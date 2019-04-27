# GRL
GRL: Groot's Runtime Library

## History
I joined a company back in 1995 that created software for Sun OS, Sun Solaris, SGI Irix, and Window NT 3.XX.  In order for them to do that they used a cross platform library called Galaxy which was owned by a company called Visix.  A little time after Java came on to the scene and a Visix thought that was going to be the future of cross platform development.  They let Galaxy stagnate and focused on a Java product.  Moving on a few years the Java product didn't sell well (I am thinking, no facts to back it up) and their bread and butter clients using Galaxy were moving on.  Visix just decided to pack up and quit.

Galaxy is now owned by a Brazilian company called Ambiencia which had appeared to have no interest in supporting any of the existing clients and so essentially killed the product.  It is still around but no one should use it anymore in my opinion.  QT, Microsoft's WPF, Xamarin, and others have subplanted Galaxy.  QT did exist at the same time when the company was looking for a cross platform library but it was very small back then and not as complete as Galaxy was.  Plus C++ compilers back then were not the same quality from platform to platform.  Also the developers the company had already were mostly FORTRAN programmers, a jump to C++ looked a little daunting for them.  C was a little more accessable.

This left us in a bit of a lurch.  So on a whim I started to make a kitchen sink library like Galaxy on my own time at home, in the hopes it would be adopted by the company.  It never was.  They opted to move to C++ and its standard library instead.  However, I use this library in my hobby coding so I still continue with the development of the library.

## State of the library
I am moving the library over bit by bit as I am documenting and tweaking some of it as I move it over.  

For instance, for a time there was no go free profiler for windows to work with.  So I had some code to do profiling built into the programs.  However this doesn't seem necessary anymore since there is Sleepy, Microprofiler, and some others which do a very good job, probably better than my more manual version.  So I am stripping some of that code out as I am moving it over.

There is no real unit tests as well and I am going to try to incorporate that into the new code as well if it does not become too much of a task.

## License.
See license file, it is BSD 2 clause. 

## Contributions
This library is a bit of a labor of love and personal.  I am not against contributions but know that I am very fussy on code style and will refactor to match.  I vehimently dislike code that has multiple personalities.  Which I have to deal with at work and it bugs me to no end as, I find, it distracts from actually understanding the code you need to work with or fix.

## Goals
The goals of the library is to provide a set of features in one place.  Kitchen Sink library.  So, memory handling, file IO, data containers, networking, etc.  All with a, hopefully, simpler interface that will be 'good enough'.  I try to make the code fast and simple but there will always be a tradeoff or two somewhere.  Not everything will be fully fleshed out either as I only develope to a point where I satisfy a need.  For example the Networking just implements simple TCP connections since I didn't need UDP at the time I was working on it.
