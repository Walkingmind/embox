

# Introduction #

Embox source codes are managed by
**[Subversion](http://en.wikipedia.org/wiki/Apache_Subversion)**
[revision control](http://en.wikipedia.org/wiki/Revision_control) system
(a.k.a **SVN**). To get an access to the source repository you will need an
[SVN client](http://en.wikipedia.org/wiki/Comparison_of_Subversion_clients).

If you have just [installed Eclipse IDE](InstallToolchainEclipse.md) you'll
probably wish to manage sources being under version control directly from your
IDE. In this article we'll take a look at how to install the most popular SVN
client plugin for Eclipse called **Subclipse**.

The installation of Subclipse is well described in
[Download and Install](http://subclipse.tigris.org/servlets/ProjectProcess?pageID=p4wYuA)
section of Subclipse project site.

**Note:** it is assumed that you have installed at least Eclipse **Helios** release
(**v3.6**). Installation procedure for older Eclipses differs and thus is not
covered here.

# Step-by-step #

## Open Eclipse Marketplace ##

From Eclipse main menu open **Help → Eclipse Marketplace...**
  * If you're using Marketplace for the first time, you will be prompted to choose a _solution catalog_. Select **Eclipse Marketplace** and press **Next >**.

## Select Subclipse for the installation ##

Find Subclipse in the plugins list and press **Install**.
> ![http://embox.googlecode.com/svn/wiki/images/InstallToolchainSubversion/eclipse-marketplace.png](http://embox.googlecode.com/svn/wiki/images/InstallToolchainSubversion/eclipse-marketplace.png)
> > Under the _Search_ tab type `subclipse` into the _Find_ field.

## Confirm Selected Features ##

By default you'll see all features included. No need to change them, so go **Next >**.

## Finish the Installation ##

You will have to _accept the terms of license agreements_ to be able to **Finish**.

**Note:** During the installation you will get _Security Warning_ message, which
notifies about installing a software from uncertified sources. This is a normal
case, so just continue the installation.

After the Software will be installed you will be prompted to restart Eclipse for
the changes to take effect.

> ![http://embox.googlecode.com/svn/wiki/images/InstallToolchainSubversion/eclipse-restart.png](http://embox.googlecode.com/svn/wiki/images/InstallToolchainSubversion/eclipse-restart.png)
> > Press **Restart Now**.

# TODO #
![http://embox.googlecode.com/svn/wiki/images/InstallToolchainSubversion/eclipse-newproject.png](http://embox.googlecode.com/svn/wiki/images/InstallToolchainSubversion/eclipse-newproject.png)
![http://embox.googlecode.com/svn/wiki/images/InstallToolchainSubversion/eclipse-reposelect.png](http://embox.googlecode.com/svn/wiki/images/InstallToolchainSubversion/eclipse-reposelect.png)
![http://embox.googlecode.com/svn/wiki/images/InstallToolchainSubversion/eclipse-repoprompt.png](http://embox.googlecode.com/svn/wiki/images/InstallToolchainSubversion/eclipse-repoprompt.png)
![http://embox.googlecode.com/svn/wiki/images/InstallToolchainSubversion/eclipse-repobrowse.png](http://embox.googlecode.com/svn/wiki/images/InstallToolchainSubversion/eclipse-repobrowse.png)

![http://embox.googlecode.com/svn/wiki/images/InstallToolchainSubversion/eclipse-team.png](http://embox.googlecode.com/svn/wiki/images/InstallToolchainSubversion/eclipse-team.png)
![http://embox.googlecode.com/svn/wiki/images/InstallToolchainSubversion/googlecode-password.png](http://embox.googlecode.com/svn/wiki/images/InstallToolchainSubversion/googlecode-password.png)
![http://embox.googlecode.com/svn/wiki/images/InstallToolchainSubversion/eclipse-commit-password.png](http://embox.googlecode.com/svn/wiki/images/InstallToolchainSubversion/eclipse-commit-password.png)