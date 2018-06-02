#create by PETS 12/10/2015
import os, sys, re, commands, subprocess, multiprocessing
import time, ctypes, shutil
from color import WTCW
def cocos_console(mode):
	try:
		retcode = subprocess.call("cocos compile -p android -m "+ mode, shell=True)
		if retcode < 0:
			print >>sys.stderr, "Child was terminated by signal", -retcode
		else:
			print >>sys.stderr, "Child returned", retcode
			if retcode == 0:
				subprocess.call("set PYTHON_ERROR=0", shell=True)
			else:
				subprocess.call("set PYTHON_ERROR=1", shell=True)
				exit(1)
	except OSError as e:
		print >>sys.stderr, "Execution failed:", e

def main():
	start = time.clock()
	console = WTCW(sys.stdout)
	if sys.argv[1] == "debug" or sys.argv[1] == "release" :
		console.writeln("\n\n{y}>>>>>>>>>>>>>>>Start Cocos Compile<<<<<<<<<<<<<< ...\n")
		console.writeln("\n{gi}--->MODE %s<--- \n"%(sys.argv[1]))
		arg = sys.argv[1]
		cocos_console(arg)
		
	end = time.clock()
	console.writeln('{gi}In %s.' % (time.strftime('%H hour(s) %M minute(s) %S second(s).\n', time.gmtime(end-start))))
if __name__ == '__main__':	
	main()