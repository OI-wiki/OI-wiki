#ifndef DETERMINISTIC_FINITE_AUTOMATON
#define DETERMINISTIC_FINITE_AUTOMATON

// --8<-- [start:dfa]
#include <algorithm>
#include <vector>
#include <queue>
#include <numeric>

// Deterministic finite automaton.
struct DFA {
    int n;   // Number of states.
    int m;   // Alphabet size.
    int q0;  // Initial state.
    std::vector<std::vector<int>> trans; // Transitions.
    std::vector<bool> acc; // Indicators for accepting states.
    DFA(int n, int m, int q0 = 0) 
    : n(n), m(m), q0(q0), trans(m, std::vector<int>(n)), acc(n) {}
    DFA hopcroft_minimize() const;
};

DFA DFA::hopcroft_minimize() const {
    // Compute inverse transitions.
    // After this step:
    // - PRE holds a permutation of all states.
    // - POS marks the starting index of each segment in PRE,
    //   where each segment contains states that transition to the same state
    //   under a specific character.
    std::vector<std::vector<int>> pre(m), pos(m);
    for (int c = 0; c < m; ++c) {
        pre[c].assign(n, 0);
        pos[c].assign(n + 1, 0);
        // Counting sort.
        for (int i = 0; i < n; ++i) ++pos[c][trans[c][i]];
        for (int i = 0; i < n; ++i) pos[c][i + 1] += pos[c][i];
        for (int i = 0; i < n; ++i) pre[c][--pos[c][trans[c][i]]] = i;
    }
    // A structure to store equivalent classes in a partition.
    // - OS (i.e., offset) is the starting index of an EC.
    // - SZ is the size of an EC. (Note that ECs are not stored in order.)
    // - CNT is a temporary counter used later.
    struct EquivClasses { 
        int os, sz, cnt;
        EquivClasses(int os = 0, int sz = 0, int cnt = 0) : os(os), sz(sz), cnt(cnt) {}
    };
    // Containers.
    std::vector<EquivClasses> ec(1);  // Current partition.
    std::vector<int> ids(n);          // A permutation of states.
    std::vector<int> par(n);          // A map from states to EC indicies.
    std::vector<bool> tag(n);         // A temporary indicator.
    std::queue<int> evidences;        // Evidences to be checked.
    // Initialize the evidence set and the partition.
    std::iota(ids.begin(), ids.end(), 0);
    ec[0].sz = std::partition(ids.begin(), ids.end(), [&](int x) -> bool { 
        return acc[x] == acc[q0]; 
    }) - ids.begin();
    if (ec[0].sz < n) {
        ec.emplace_back(ec[0].sz, n - ec[0].sz, 0);
        evidences.push(ec[0].sz < ec[1].sz ? 0 : 1);
        for (int i = ec[1].os; i < n; ++i) {
            par[ids[i]] = 1;
        }
    }
    // Iterations.
    while (!evidences.empty()) {
        auto cr = evidences.front();
        evidences.pop();
        for (int c = 0; c < m; ++c) {
            // Collect possibly affected equivalent classes.
            std::vector<int> todo;
            for (int i = ec[cr].os; i < ec[cr].os + ec[cr].sz; ++i) {
                for (int k = pos[c][ids[i]]; k < pos[c][ids[i] + 1]; ++k) {
                    auto j = pre[c][k];
                    if (!tag[j]) {
                        if (!ec[par[j]].cnt) todo.push_back(par[j]);
                        ++ec[par[j]].cnt;
                        tag[j] = true;
                    }
                }
            }
            // Split classes whenever needed.
            for (int i : todo) {
                int ti = i;
                if (ec[i].cnt != ec[i].sz) {
                    // Add the smaller segment to the end of the equivalent classes.
                    bool majority_tagged = ec[i].cnt * 2 >= ec[i].sz;
                    int mid = std::partition(
                        ids.begin() + ec[i].os, ids.begin() + ec[i].os + ec[i].sz,
                        [&](int x) -> bool { return tag[x] == majority_tagged; } 
                    ) - ids.begin() - ec[i].os;
                    for (int j = ec[i].os + mid; j < ec[i].os + ec[i].sz; ++j) {
                        par[ids[j]] = ec.size();
                    }
                    evidences.push(ec.size());
                    if (!majority_tagged) ti = ec.size();
                    ec.emplace_back(ec[i].os + mid, ec[i].sz - mid, 0);
                    ec[i].sz = mid;
                }
                // Clear the temporary counter and indicators.
                ec[i].cnt = 0;
                for (int j = ec[ti].os; j < ec[ti].os + ec[ti].sz; ++j) {
                    tag[ids[j]] = false;
                }
            }
        }
    }
    // Output.
    DFA res(ec.size(), m, par[q0]);
    for (const auto& e : ec) {
        auto i = ids[e.os];
        res.acc[par[i]] = acc[i];
        for (int c = 0; c < m; ++c) {
            res.trans[c][par[i]] = par[trans[c][i]];
        }
    }
    return res;
}

// --8<-- [end:dfa]
#endif // DETERMINISTIC_FINITE_AUTOMATON
