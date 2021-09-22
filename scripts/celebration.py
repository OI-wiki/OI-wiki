import requests
import json
import sys

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

id = res['id']
stars = res['stargazerCount']
issues = res['issues']['nodes']
numbers = []

maxCelebration = 0
for issue in issues:
    numbers.append('#' + str(issue['number']))
    maxCelebration = max(maxCelebration, int(issue['title'].split(' ')[0]))

celebration = maxCelebration * 2

if stars >= celebration - 1: # "will soon" reach
    mutation = f'''
mutation {{
  createIssue(input: {{
    repositoryId: "{id}",
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

最后，祝大家身体健康，我们 {celebration * 2} stars 时再见。

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
