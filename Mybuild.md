**Mybuild** is build automation and configuration tool oriented on building modular applications.

Mybuild itself is implemented on top of [GNU Make](http://www.gnu.org/software/make/) utilizing the power of incremental and parallel building of the latter.
This also allows one to embed Mybuild into an existing Make-powered build infrastructure.
At the same time, despite of using Make, Mybuild uses own [syntax](MybuildLanguageReference.md) devoid of drawbacks of the language of Makefiles.

# Workflow #

A typical workflow of developing a Mybuild-driven project involves two kinds of people:

<table width='839' cellspacing='10'><tr valign='top'><td width='50%'>

<h2>Developers</h2>
<blockquote>who need to maintain build files for the component they are working on.<br>
</td><td></blockquote>

<h2>Users</h2>
<blockquote>who just want to build the (maybe with different configurations).<br>
</td></tr></table></blockquote>

_Well, there are also developers of Mybuild itself, but we don't consider them for now._ So, there are two different types of the build files, accordingly to the intended audience:

<table width='839' cellspacing='10'><tr valign='top'><td width='50%'>

<h2>My-files</h2>
<blockquote>are used to describe all buildable modules of the application, their relationships and available configuration options. These files are written by the application developers and usually placed in the source tree.<br>
<pre><code>module HelloWorld {<br>
    source "hello.c"<br>
}<br>
</code></pre>
Proper names for my-files are <b><code>Mybuild</code></b> and <b><code>*.my</code></b>.<br>
</td><td></blockquote>

<h2>Config-files</h2>
<blockquote>contain directives to build certain modules with values for their options. These files are assumed to be constructed by the users, however developers can provide templates with reasonable defaults.<br>
<pre><code>configuration Main {<br>
    include HelloWorld<br>
}<br>
</code></pre>
Configuration files are named <b><code>*.config</code></b>.<br>
</td></tr></table></blockquote>

Both files are regular text files (no XML!) that can be edited in any text editor. There is also a [plug-in](InstallMybuildEclipsePlugin.md) for Eclipse IDE, which provides rich editing facilities including syntax highlighting, content proposals, more powerful error reporting and so on.

After necessary my- and config-files are ready one can build the project typing `make`. Based on the build files Mybuild will infer what needs to be built automatically.

To summarize, the build process can be represented as follows:

<table align='center'><tr><td>
<img src='http://embox.googlecode.com/svn/wiki/images/Mybuild/mybuild-workflow.png' />
</td></tr></table>

# What's next? #
The complete language reference for my- and config-files is available [here](MybuildLanguageReference.md).

To get more detailed understanding of how Mybuild actually builds the project please check [build sequence page](MybuildBuildSequence.md).

Finally, in case if you're interested about how Mybuild itself is implemented, you may check [internal structure section](MybuildInternalsOverview.md).