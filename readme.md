# Project Title


PaTuCel 1stTry v0.0.1

## Prerequisites

### Project Tools
* [Cocos2dx](http://www.cocos2d-x.org/download) - Version 3.17
* [Git](https://git-scm.com/) - Download Latest Version
* [Cocos Creator](http://www.cocos2d-x.org/creator) - V1.911 WIN
* [Tiled Map Editor](https://thorbjorn.itch.io/tiled) - installer (without Python support)

### Win32
* [Visual2017](https://www.visualstudio.com/es/free-developer-offers/) - Visual Studio Community
* [C++ Redistributable](https://www.microsoft.com/en-us/download/details.aspx?id=30679#) - Visual C++ Redistributable for Visual Studio 2012 Update 4
	* ![alt text](https://github.com/PatuCel/FirstTry/blob/master/docs/Visual2017.png)

### Android
* [Python](https://www.python.org/downloads/windows/) - Version 2.7 (For cocos commands)
* [Android NDK](https://developer.android.com/ndk/downloads/) - Lastest version
* [Apache ANT](https://ant.apache.org/bindownload.cgi) - Version 1.9.11

## Optional Tools

### Git Flow Scheme
* ![alt text](https://github.com/PatuCel/FirstTry/blob/Develop/docs/git-workflow-release-cycle-4maintenance.png)
	* [Git Flow Tool](https://github.com/nvie/gitflow/wiki/Windows)
		* You need to install [Cygwin](http://www.cygwin.com/) with **util-linux** and **wget**
		* Add Cygwin in the PATH folder 
		* Then simply run this command from a Cygwin shell, open CMD and TYPE $bash to enter cygwin shell
			* ```$wget -q -O - --no-check-certificate https://github.com/nvie/gitflow/raw/develop/contrib/gitflow-installer.sh | bash```
* [GitHub Desktop](https://desktop.github.com/) - GitHub Desktop app
* [GitKraken](https://www.gitkraken.com/download) - GitKraken last version
* [TortoiseGit](https://tortoisegit.org/) - TortoiseGit is a Windows Shell Interface to Git and based on TortoiseSVN
* [Atom](https://atom.io/) - Like Sublime but has Git build inside the editor.

## Build Resources

### cocos creator

* Build Resources
	* ![alt text](https://github.com/PatuCel/FirstTry/blob/Develop/docs/cocosCreatorSetup.png)
	* ![alt text](https://github.com/PatuCel/FirstTry/blob/Develop/docs/cocosCreatorBuild.png)

## Compilation steps

### Android
* Make Sure you run the setup.py insiede the cocos3.17 folder
	* Then open your Enviroment Variables and Check if your **NDK_ROOT** is set to android-ndk-r17 and you **ANDROID_SDK_ROOT** is set to your lastest sdk for example: **C:\Users\finalpets\AppData\Local\Android\Sdk**
```
	buildAndroid.bat
```
### Win32
* Open solution project inside of proj.win32/FirstTry.sln or run:
`buildWin32.bat`

## Documentation

* [Cocos2dx](http://www.cocos2d-x.org/docs/cocos2d-x/en/index.html)
	* [Cocos2dx Api](http://www.cocos2d-x.org/docs/api-ref/cplusplus/v3x/)
* [Cocos Creator](http://cocos2d-x.org/docs/creator/manual/en/)
	* [Cocos Creator Api](http://www.cocos2d-x.org/docs/creator/api/en/)
* [Git](https://git-scm.com/doc)
* [TortoiseGit](https://tortoisegit.org/docs/tortoisegit/)
* [GitHub Desktop](https://help.github.com/desktop/)
* [Git Flow](https://github.com/nvie/gitflow/wiki)

## Free Assets

* [OpenGameArt](https://opengameart.org/)

