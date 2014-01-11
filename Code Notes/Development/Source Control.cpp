//////////////////////////////////////////////////////////////////////////////
//GIT SOURCE CONTROL
//////////////////////////////////////////////////////////////////////////////
/*

INITIALISE GIT
git config --global user.name "Kara Jensen"
git config --global user.email mail@karajensen.com
git config --global merge.tool kdiff3

CLONE REPOSITORY
git clone https://github.com/karajensen/cloth-simulator.git folderName

ADD REMOTE REPOSITORY
git remote add master https://github.com/karajensen/cloth-simulator.git

IGNORING FILES (use a .gitignore file)
# ignore all .a files
*.a
# still track lib.a, even though you're ignoring .a files above
!lib.a
# ignore all files in the build/ directory
build/
# ignore doc/notes.txt, but not doc/server/arch.txt
doc/*.txt

IGNORING FILES ONCE PUSHED
git rm -r --cached file.txt

LIST ALL BRANCHES
git branch

CREATE NEW BRANCH
git fetch origin //gets updates from server
git checkout -b myBranch origin/ParentBranch
git push -u origin myBranch //creates remote branch

CHECKOUT A BRANCH
git checkout myBranch

SHOW CHANGED FILES IN BRANCH
git status

ADD CHANGES TO NEXT COMMIT
git add -A

COMMIT CHANGES
git commit -am "Description"

DISCARD ALL UNCOMMITED CHANGES
git reset --hard

REVERT BACK TO COMMIT
git reset --hard commitid
[get commitid from the git log second column]

PUSH LOCAL CHANGES TO REMOTE
git push
git push origin master

MERGE REMOTE BRANCH INTO CURRENT BRANCH
git pull origin ParentBranch

MERGE CONFLICTS
git mergetool

DELETE LOCAL BRANCH
git branch -d myBranch

DELETE REMOTE BRANCH
git push origin --delete myBranch

RENAMING A BRANCH
git branch -m old_branch new_branch
git push origin -u new_branch
git push origin --delete old_branch

SHOW REMOTE BRANCH OF LOCAL
git remote show origin

*//////////////////////////////////////////////////////////////////////////////