# Contributing to MathJax

You are interested in giving us a hand? That's awesome! We've put together some brief guidelines that should help you get started quickly and easily.

There are lots and lots of ways to get involved, this document covers:

* [reporting an issue](#reporting-an-issue)
    * [bug reports](#bug-reports)
    * [feature requests](#feature-requests)
    * [change requests](#change-requests)
* [working on MathJax core](#working-on-mathjax-core)
    * [key branches and tags](#key-branches--tags)
    * [submitting pull requests](#submitting-pull-requests)
    * [testing and quality assurance](#testing-and-quality-assurance)
    * [writing documentation](#writing-documentation)
    * [translation](#translation)
* [Conduct](#conduct)


## Reporting An Issue

If you're about to raise an issue because you think you've found a
problem with MathJax, or you'd like to make a request for a new
feature in the codebase, or any other reason… please read this first.

The GitHub issue tracker is the preferred channel for [bug reports](#bug-reports),
[feature requests](#feature-requests), [change requests](#change-requests) and [submitting pull
requests](#submitting-pull-requests), but please respect the following restrictions:

* Please **search for existing issues**. Help us keep duplicate issues
  to a minimum by checking to see if someone has already reported your
  problem or requested your idea.

* Please **do not** use the issue tracker for personal support
  requests (use [the MathJax User Group](https://groups.google.com/forum/#!forum/mathjax-users)).

* Please **be civil**. Keep the discussion on topic and respect the
  opinions of others. See also our [Conduct Guidelines](#conduct)

### Bug Reports

A bug is a _demonstrable problem_ that is caused by the code in the repository.
Good bug reports are extremely helpful - thank you!

Guidelines for bug reports:

1. **Use the GitHub issue search** &mdash; check if the issue has already been
   reported.

2. **Check if the issue has been fixed** &mdash; look for [closed issues in the
   current milestone](https://github.com/MathJax/MathJax/issues?&page=1&state=closed) or try to reproduce it
   using the latest `develop` branch. Please note that we only pack MathJax for releases, so on the `develop` branch you have to use `/unpacked/MathJax.js` etc. to test.

3. **Share a live sample of the problem** &mdash; without a live page it is usually impossible to debug problems; see also the Bug Report Template below.

4. **Isolate the problem** &mdash; a live sample is a starting point but if you want to speed things up create a [reduced test
   case](http://css-tricks.com/6263-reduced-test-cases/). Be specific about your setup (browser, OS versions etc). Use services like [jsbin](http://jsbin.com), [CodePen](http://codepen.io), [JSfiddle](http://jsfiddle.com) to make collaboration on minimal test cases easier for everyone. Use the unpacked copy of MathJax (`[...]/unpacked/MathJax.js` etc.) for better debugging.

5. **Include a screenshot/cast as a last resort** &mdash; Is your issue about a layout
   or design feature / bug but hard to reproduce or isolate? Then please provide a screenshot or screencast. Tools like [LICEcap](http://www.cockos.com/licecap/) or [SauceLabs](http://www.saucelabs.com) allow you to quickly and easily record a screencasts. Make it an animated gif, embed it directly into your GitHub issue -- kapow!

6. Use the Bug Report template below or [click this
   link](https://github.com/MathJax/MathJax/issues/new?title=Bug%3A&body=%23%23%23%20Issue%20Summary%0A%0A%23%23%23%20Steps%20to%20Reproduce%0A%0A1.%20This%20is%20the%20first%20step%0A%0AThis%20is%20a%20bug%20because...%0A%0A%23%23%23%20Technical%20details%0A%0A*%20MathJax%20Version%3A%20master%20-%20latest%20commit%3A%20%20INSERT%20COMMIT%20REF%0A*%20Client%20OS%3A%20%0A*%20Browser%3A%20%0A*%20)
   to start creating a bug report with the template automatically.

A good bug report shouldn't leave others needing to chase you up for
more information. Be sure to include the details of your environment.

Here is a [real example](https://github.com/mathjax/MathJax/issues/820)

Template Example ([click to use](https://github.com/MathJax/MathJax/issues/new?title=Bug%3A&body=%23%23%23%20Issue%20Summary%0A%0A%23%23%23%20Steps%20to%20Reproduce%0A%0A1.%20This%20is%20the%20first%20step%0A%0AThis%20is%20a%20bug%20because...%0A%0A%23%23%23%20Technical%20details%0A%0A*%20MathJax%20Version%3A%20master%20-%20latest%20commit%3A%20%20INSERT%20COMMIT%20REF%0A*%20Client%20OS%3A%20%0A*%20Browser%3A%20%0A*%20)):
```
Short and descriptive example bug report title

### Issue Summary

A summary of the issue and the browser/OS environment in which it occurs. If
suitable, include the steps required to reproduce the bug.

### Steps to Reproduce

1. This is the first step
2. This is the second step
3. Further steps, etc.

Any other information you want to share that is relevant to the issue
being reported. Especially, why do you consider this to be a bug? What
do you expect to happen instead?

### Technical details:

* MathJax Version: 2.3 (latest commit: f3aaf3a2a3e964df2770dc4aaaa9c87ce5f47e2c)
* Client OS: Mac OS X 10.8.4
* Browser: Chrome 29.0.1547.57
```


### Feature Requests

Feature requests are welcome. Before you submit one be sure to have:

1. Read the
   [Roadmaps](https://github.com/mathjax/MathJax/wiki/Mathjax-roadmap),
   **use the GitHub search** and check the feature hasn't already been
   requested.
2. Take a moment to think about whether your idea fits with the scope
   and aims of the project, or if it might better fit being a [custom
   extension](https://github.com/mathjax/MathJax-third-party-extensions).
3. Remember, it's up to *you* to make a strong case to convince the
   project's leaders of the merits of this feature. Please provide as
   much detail and context as possible, this means explaining the use
   case and why it is likely to be common.
4. Clearly indicate whether this is a feature request for MathJax
   core, input & output jax, or extensions.


### Change Requests

Change requests cover both architectural and functional changes to how
MathJax works. If you have an idea for a new or different dependency,
a refactor, or an improvement to a feature, etc - please be sure to:

1. **Use the GitHub search** and check someone else didn't get there first
2. Take a moment to think about the best way to make a case for, and
   explain what you're thinking. Are you sure this shouldn't really be
   a [bug report](#bug-reports) or a [feature
   request](#feature-requests)?  Is it really one idea or is it many?
   What's the context? What problem are you solving? Why is what you
   are suggesting better than what's already there? Does it fit with
   the Roadmap?

## Working on MathJax core

You want to contribute code? Fantastic! Let's get you started.

### Key Branches & Tags

To get it out of the way:

- **[develop](https://github.com/MathJax/MathJax/tree/develop)** is
  the development branch. All work on the next release happens here so
  you should generally branch off `develop`. Do **NOT** use this branch
  for a production site. 
- **[master](https://github.com/MathJax/MathJax)** contains the latest
  release of MathJax. This branch may be used in production. Do 
  **NOT** use this branch to work on MathJax's source.

### Submitting Pull Requests

Pull requests are awesome. If you're looking to raise a PR for
something which doesn't have an open issue, please think carefully
about [raising an issue](#reporting-an-issue) which your PR can close,
especially if you're fixing a bug. This makes it more likely that
there will be enough information available for your PR to be properly
tested and merged.

##### Need Help?

If you're not completely clear on how to submit / update / *do* Pull
Requests, please check out our [source control
policies](https://github.com/mathjax/MathJax/wiki/Source-control-policies). For
more insights, chech the excellent in depth [Git Workflow
guide](https://github.com/TryGhost/Ghost/wiki/Git-Workflow) from
Ghost, in particular

* [Ghost Workflow guide: commit messages](https://github.com/TryGhost/Ghost/wiki/Git-workflow#commit-messages)

### Testing and Quality Assurance

Never underestimate just how useful quality assurance is. If you're
looking to get involved with the code base and don't know where to
start, checking out and testing a pull request is one of the most
useful things you could do.

If you want to get involved with testing MathJax, there is a set of QA
Documentation [in our testing
framework](https://github.com/MathJax/MathJax-test).

Essentially though, [check out the latest develop
branch](#working-on-mathJax-core), take it for a spin, and if you find
anything odd, please follow the [bug report guidelines](#bug-reports)
and let us know!

#### Checking out a Pull Request

These are some [excellent
instructions](https://gist.github.com/piscisaureus/3342247) on
configuring your GitHub repository to allow you to checkout pull
requests in the same way as branches:
<https://gist.github.com/piscisaureus/3342247>.


### Writing documentation

MathJax's main documentation can be found at [docs.mathjax.org](http://docs.mathjax.org).
The source of the docs is hosted in the
[mathjax/mathjax-docs](http://github.com/mathjax/mathjax-docs) repo here on GitHub.

The documentation is generated using [Sphinx-doc](http://sphinx-doc.org/) and hosted on 
[Read the docs](http://readthedocs.org).
You can clone the repo and submit pull requests following the
[pull-request](#submitting-pull-requests) guidelines.


### Translation

If you wish to add or update translations of MathJax, please do it on
[TranslateWiki.net](https://translatewiki.net/w/i.php?title=Special:Translate&group=out-mathjax-0-all)
(and while you're there you can help other open source projects,
too, because you're awesome!).

For bug reports and other questions that don't fit on
TranslateWiki.net, head over to the
[mathjax/mathjax-i18n](https://github.com/mathjax/MathJax-i18n)
repository.

## Conduct

We are committed to providing a friendly, safe and welcoming environment for
all, regardless of gender, sexual orientation, disability, ethnicity, religion,
or similar personal characteristic.

Please be kind and courteous. There's no need to be mean or rude.
Respect that people have differences of opinion and that every design or
implementation choice carries a trade-off and numerous costs. There is seldom
a right answer, merely an optimal answer given a set of values and
circumstances.

Please keep unstructured critique to a minimum. If you have solid ideas you
want to experiment with, make a fork and see how it works.

We will exclude you from interaction if you insult, demean or harass anyone.
That is not welcome behaviour. We interpret the term "harassment" as
including the definition in the
[Citizen Code of Conduct](http://citizencodeofconduct.org/);
if you have any lack of clarity about what might be included in that concept,
please read their definition. In particular, we don't tolerate behavior that
excludes people in socially marginalized groups.

Private harassment is also unacceptable. No matter who you are, if you feel
you have been or are being harassed or made uncomfortable by a community
member, please contact one of the channel ops or any of the
[MathJax](https://github.com/MathJax/MathJax) core team
immediately. Whether you're a regular contributor or a newcomer, we care about
making this community a safe place for you and we've got your back.

Likewise any spamming, trolling, flaming, baiting or other attention-stealing
behaviour is not welcome.

We also suggest to read [discourse's
rules](http://blog.discourse.org/2013/03/the-universal-rules-of-civilized-discourse/)

## References

* We heavily borrowed from Mozilla and Ghost -- thank you!
  * https://github.com/TryGhost/Ghost/blob/master/CONTRIBUTING.md
  * https://github.com/mozilla/rust/wiki/Note-development-policy
* https://github.com/jden/CONTRIBUTING.md/blob/master/CONTRIBUTING.md
* http://blog.discourse.org/2013/03/the-universal-rules-of-civilized-discourse/
