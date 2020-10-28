# Contributing guidelines

## Issues
### New topic request
The request must include at least the following:
 - A short explanation of the topic and why it's usefull
 - At least one link to an (wikipedia) article/ blog post explaining the topic
 - An overview of functions that interface with the rest of the code
 - An estimate of code length in columns (55 code lines+header)
    - Examples: Treap: 2 columns; Union Find: 0.2 column; ...

### Other issues
No real constraints except give a clear description

## Pull requests
### General
I use a rebase workflow. That means that pull requests will only be considered when the source branch has been rebased onto the latest commit of the target branch. Furthermore the history of the source (and target) branch must be linear. To aid in this `pull.rebase` has been set to true, which means `git pull` will do `fetch→rebase` instead of `fetch→merge`.

**But... I'm scared of rebase**
Don't worry, rebasing isn't that hard. You just have to go trough it a couple of times to realize it is not that bad. If you run into problems I can help you in a pull request. Below is how you rebase your branch onto branch `main` of this repository:
```sh
git remote add spaanse git@github.com:spaanse/TeamReferenceDocument.git
git fetch spaanse
git branch restore # Add if you are really unsure about your rebasing skills
git rebase spaanse/main
git rebase --abort # To stop the rebase if you have any merge conflicts you don't want to resolve
git reset --hard restore # If somehow something went wrong
git push -f
```
If you are still scared use a git client. I do, so there is no shame in that. Even if you are not scared of git this is a good idea because you can actually understand what happens. Otherwise you might not even have known that `git pull` is a synonym of `git fetch` and `git merge`.

### New code/text
The pull request must either link a "new topic" issue or satisfy the first two requirements of "new topic" issues. If the topic requires code there must be two versions of that code: a short version under `code` that will be added to the TRD and a longer version under `longcode` that is readable and usefull for someone learning the topic. All new code must adhere to the coding conventions listed below.

### Modifying existing code/text
After the modifications the modified code must still adhere to the coding conventions. If the short code is changed, the long code must also be modified to reflect that. If there is no long code for the changed code this requirement is waved. Also `reference.tex` may need to be modified to maintain a nice layout.

## Coding Conventions 
All code must compile without errors/warnings using the flags `-Wall -Wextra -Wshadow`.

The short code (under `code`) must be as compact as possible while maintaining a low standard of readability. Below are some guidelines:

 - Every line contains at most 44 characters
 - There should be a hash clearing comment `//...` before the segment included in the TRD.  
   The TRD describes how to find the right value of `...`.
 - Lines are tab-indented, a tab counts as two characters for the character limit.
 - Only combine lines into a single line if they somewhat relate.
 - If possible without making more lines, align similar text with the previous line using spaces.  
   This might mean you indent using tabs to the start of the previous line and then indent further using spaces.  
   Using this method keeps the alignment even if the tab width is changed.
 - All code included in the TRD is either a single function, one or more structs, or in a namespace.
 - The content of `struct` and `namespace` don't need extra indentation.
 - Functions,structs and enums that are to be used outside of the code segment should have clear names. They may use abbreviations, but can't have a name consisting of a single letter.
 - Single-character variables are allowed (as they are needed to fit in 44 chars). Make the name as descriptive as possible (so use `l/r` for left/right, use `n` for node and `t` for tree/subtree, `ijk` as indices etc.)
 - Preferably use `if{__;__;}` over `if __,__;` in `if`/`for`/`while` statement's content.
 - Avoid a line starting with `}` except as "`} else {`", instead tuck the `}` it at the end of the previous line.
 - Preferably add comments on their own line to explain what functions do, unless that is clear from comments of previous functions or would make the code so long that a new column would be needed.
 - Preprocessor commands should not be used.
 - Tip: the regex `(?(?=\w) (?!\w)| )` matches all spaces that can be safely removed.

The long code (under `longcode`) must be readable, but semantically equivalent to the short version. That means that in general code should not be reordered. Some clear distinctions to the short code:

 - There is a soft line length limit of 80 chars, and a hard limit of 120 chars. Tabs count as 4 characters.
 - No single letter variables.
    - `ijk` as indices are sometimes exempt if there is no clearer name for them.
    - For example in Floyd-Warshall use `from`,`to`,`via` instead of `i`,`j`,`k`.
 - Opening brace after statement, closing brace on it's own line but may be followed by an `else`.
 - Lines should have a single statement on them.
 - Code should be heavily commented:
    - All functions should have a comment describing what the function does,
    - All variables should have a comment describing what it stores (especially DP tables)
    - Add comments explaining tricks used (for example with bit manipulation).
 - Add spaces around any binary operators. Add parentheses `()` if the order of operations is not clear.
 - The hash-manipulating lines may be left out.
 - Indentation happens in the same way: tabs, extra alignment with spaces.

The LaTeX (`reference.tex`) also has requirements:

 - 4-column layout, but the left two and right two columns may be combined.
    - So `1/1/1/1` or `1/1/2` or `2/1/1` or `2/2` but not `3/1` or `1/2/1`.
    - The multicols environment is restarted for each page.
 	- At the end of each quarter column there must be a `\vfill\null`
 	- Going to the next column is done using `\columnbreak`
 - Code segments have the width of one quarter column.
    - Code segments may span multiple columns, but then is manually split to prevent splitting in unfortunate places.
 - Mathematics is either inline or within a `flalign*` block