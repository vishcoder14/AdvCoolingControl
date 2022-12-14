# backup_project.py

''' Python code for backup, vscode current workspace directory 
		this code will backup all the folder and subfolder of
		current file's directory. Paste this script to the directory
		whose content wants to be backuped '''

# [vishnus_technologies (C) 2022]
# --------------------------------------------------------------


import os 
import shutil

src = os.path.dirname(os.path.realpath(__file__))
def_dst = "D:/project_backup_vscode/"

_msg = "\nPython program for project backup (AdvCoolingControl)\n"
print(_msg)
dst = input("Enter the destination directory: ")

if(len(dst) == 0):
	print("[MSG: You have entered nothing, setting this directory\n      {" +def_dst+"} as default destination folder]\n")
else:
  if(os.path.exists(dst)):
    print("directory entered: "+dst+" is validated")
    shutil.copytree(src, dst)
    