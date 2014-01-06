FlatTurtle InfoScreenBrowser
============================

This repository is for developers only. If you want a FlatTurtle at your company, please check out https://FlatTurtle.com. Thank you and see you soon!

If you're a developer, this is our browser which will render the HTML5 InfoScreen. It gives us extra features towards screen-control. Through an XMPP session to our servers you can control a screen using push messages. Later on we're planning on adding XMPP support for data interchange.

Requirements
------------

- Qt >= 4.6
- A FlatTurtle InfoScreen server
- libqxmpp >= 3.0
- An XMPP server (optional)
- The DataTank (optional)

Note: When compiling, don't forget to alter your config.ini in src/

Installation
------------

1. Install your [FlatTurtle MyTurtle](https://github.com/FlatTurtle/MyTurtle)
2. Install a [The DataTank](https://github.com/iRail/The-DataTank) instance and load the right resources
3. Link the Turtles in your FlatTurtle InfoScreen to your The DataTank instance.
4. Install this repository on an embedded device after you compiled it
5. You can now add different settings and customize your set-up.
6. Done!

InfoScreen purpose
------------------

The purpose of this project is to give more visibility to public transport around your office. Using [MyTurtleAdmin](https://github.com/FlatTurtle/MyTurtleAdmin) you can specify your location and the desired stations you want to display on the screen which may be placed at the entrance.

This is a project started by the FlatTurtle bvba. It's the back-end for our mobility-screen and digital signage products. 

FlutTurtle is member of the iRail NPO. The copyright of this software is maintained by the non profit organisation and licensed under AGPL. We do not however include the designs which contain company logos and styles from the companies we work for. You are free however to make this code better and/or to use it for your own project (as long as you respect the AGPL).

iRail
-----

More information can be found on [iRail](https://hello.irail.be/).

FlatTurtle
----------

More information can be found on [FlatTurtle](https://FlatTurtle.com/) and on the [dev-site](http://dev.flatturtle.com/).

License
-------

GPLv3

(c) 2011-2014 FlatTurtle

Some interesting links
-----------------------
* http://s.flatturtle.com/demo/view/stable/ - a DEMO
* http://data.irail.be - our API
* http://hello.iRail.be - The iRail project



