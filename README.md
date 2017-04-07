# mike-and-conquer-4


Notes:

In order to run in TESTMODE and allow the app to open a specific IP address for testing, the app must be run as administrator.
Similarly, to  debug remotely, the Remote Debugger must be run as administrator
To debug remotely and have the game accept test drier Rest calls, the firewall must be setup correctly. 


* To run unit tests, set mike-and-conquer-test as Startup project, and run with CTRL-F5

* When loading Visual Studio for the first time, you may need to use NuGet to pull C++ Rest SDK.
See here:  https://casablanca.codeplex.com/wikipage?title=Using%20NuGet%20to%20add%20the%20C%2B%2B%20REST%20SDK%20to%20a%20VS%20project
for how to do this