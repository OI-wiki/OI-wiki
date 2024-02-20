import requests
import json
import sys
from datetime import datetime
from math import log2

def nextCelebration(current):
    a = (current // 5000 + 1) * 5000
    b = 2 ** (int(log2(current)) + 1)
    return min(a, b)

headers = {
    "Authorization": f'token {sys.argv[1]}'
}

label = "Celebration / 庆贺"

query = f'''
query {{
    repository(owner: "OI-wiki", name: "OI-wiki") {{
        id
        stargazerCount
        label(name: "{label}") {{
            id
        }}
        issues(labels: "{label}", first: 100) {{
            nodes {{
                number
                title
                createdAt
                closed
                id
            }}
        }}
        defaultBranchRef {{
            target {{
                ... on Commit {{
                    history {{
                        totalCount
                    }}
                }}
            }}
        }}
    }}
}}
'''

res = requests.post('https://api.github.com/graphql', json.dumps({'query': query}), headers = headers).json()['data']['repository']

repositoryId = res['id']
stars = res['stargazerCount']
issues = res['issues']['nodes']
numbers = []

maxCelebration = 0
for issue in issues:
    numbers.append('#' + str(issue['number']))
    maxCelebration = max(maxCelebration, int(issue['title'].split(' ')[0]))
    timeDelta = (datetime.now() - datetime.fromisoformat(issue['createdAt'][0:-1]))
    if timeDelta.days >= 7 and not issue['closed']:
        mutation = f'''
mutation {{
    closeIssue(input: {{ issueId: "{issue['id']}"}}) {{
        issue {{
            number
            closed
        }}
    }}
}}
'''
        print(mutation)
        mut = requests.post('https://api.github.com/graphql', json.dumps({ 'query': mutation }), headers = headers)
        print(mut.text)

celebration = nextCelebration(maxCelebration)

if stars >= celebration - 1: # "will soon" reach
    mutation = f'''
mutation {{
  createIssue(input: {{
    repositoryId: "{repositoryId}",
    title: "{celebration} Stars Celebration",
    labelIds: ["{res['label']['id']}"],
    body: {json.dumps(f"""> To celebrate that our project's stars will soon reach {celebration}.
> This issue will be closed in one week.

为庆祝我们的 **OI Wiki** 项目 Stars 即将到达 {celebration}，特开此 Issue，大家也放松下。

诸位维护本项目也都辛苦了，我刚刚看了下 Commits 也到达了 {res['defaultBranchRef']['target']['history']['totalCount']}，大家在本 Issue 里面想说什么就说什么吧（But please don't spam in this issue）。

祝大家愉快。

<!--（文案来自 @K-Guan）-->

***

非常感谢这么长时间以来大家的支持，我们再接再厉～

最后，祝大家身体健康，我们 {nextCelebration(celebration)} stars 时再见。

cc {" ".join(numbers)}
""", ensure_ascii = False)}
  }}) {{
    issue {{
      number
    }}
  }}
}}
'''
    print(mutation)
    mut = requests.post('https://api.github.com/graphql', json.dumps({ 'query': mutation }), headers = headers)
    print(mut.text)
