#ST2512: Programming in Security - C Programming Assignment
#####NOTE: The files to work on is inside the folder "Source Code".


##Basics on how to use GitHub
[Click here](https://www.youtube.com/watch?v=0fKg7e37bQE)


##How to use git in Ubuntu to push and pull changes
[Click here](https://www.howtoforge.com/tutorial/install-git-and-github-on-ubuntu-14.04/)


##Key terminal commands for git
####Before you clone this repository, make a new directory to store all your GitHub repositories:
```
mkdir ~/github
cd ~/github
```

#####To add this repository to your computer:
```
git clone https://github.com/zxlim/PSE2016-Cprog.git
```

####The commands below will only work if you are in the repository folder. Do this then proceed on:
```
cd ~/github/PSE2016-Cprog
```

#####To check repository status:
```
git status
```

#####To pull changes from repository (Get latest files):
```
git pull
```

#####To add some changes to be committed to repository (Select edited files for upload):
```
git add [filename]
```

#####To add ALL changes to be committed to repository (Same as above but ALL files):
```
git add .
```

#####To commit such changes to repository (Confirm the edits and prepare for upload):
```
git commit -m "[additional notes here]"
```

For additional notes, type in what you have modified e.g. "Added in a loop statement for the word check" etc.

#####To push changes to repository (Upload latest files):
```
git push
```


##Important Note
If you wish to compile and test the source code (game.c), please do so in the folder "Compiled" under the folder "PSE2016-Cprog". Use the following command to compile (Replace x with version number e.g. v1.0, v2.3 etc):
```
cd ~/github/PSE2016-Cprog/Source\ Code/
cc -Wall game.c util.c -o ../Compiled/game_x
```
P.S. The flag "-Wall" will prevent compilation of source code if there's any warning or error. It's to play super safe.


The folder "Original" contains the original files provided in Blackboard.
