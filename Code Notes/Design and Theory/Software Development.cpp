//////////////////////////////////////////////////////////////////////////////
//SOFTWARE DEVELOPMENT
//////////////////////////////////////////////////////////////////////////////
/*

AGILE
• Uses self-organizing teams
• Uses time-boxed iterative approach
• Encourages rapid and flexible response to change
• Each iteration involves one team working on planning, design, coding and testing
• At end of each iteration product is demonstrated to stakeholders
• Goal is to have an available release at the end of each iteration
• Have a daily standup or daily scrum meeting 

SCRUM
• Product Owner: represents the stakeholders; ensures team delivers value to business
• Product Owner writes user stories, prioritizes and adds them to the backlog
• ScrumMaster: acts as buffer between team and any problems, not the team leader
• Stakeholders: customers of the product
• Scrum of scrums: team representitives have a 'standup' meeting
• Retrospective to reflect on how the iteration went

//////////////////////////////////////////////////////////////////////////////
//SOFTWARE TOOLS
//////////////////////////////////////////////////////////////////////////////

FUSLOGVW.EXE
Displays details for failed assembly binds. Allows diagnosing why .NET framework
cannot locate an assembly at runtime (TypeLoadException)

DEPENDS.EXE
Dependency walker for 32/64 bit modules (dll,exe) and builds heirarchical tree
diagrams of all dependent modules, shows exported functions

//////////////////////////////////////////////////////////////////////////////
//GIT SOURCE CONTROL
//////////////////////////////////////////////////////////////////////////////

INITIALISE GIT
git config --global user.name "Kara Jensen"
git config --global user.email KaraPeaceJensen@gmail.com
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

*//////////////////////////////////////////////////////////////////////////////