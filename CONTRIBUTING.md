# Contributing guidelines
## Creating good bug report
Sometimes software can have some nasty bugs that messing with our life.

If you want to create a good bug report, check if it meets the following criterias:
- Avoid duplicates: Search before you file!
- Always test the latest available version **or** commit.
- One bug per report.
- State useful facts and/or steps to reproduce, not opinions or complaints.
- Specify the name and version of the OS you're using.

### Bug report example
For version build from github sources:

```
**Bug description**
Game crushes on ENTER

**Steps to reproduce**
 1. Launch the game
 2. Press Enter

**System information**
OS: Windows 10 Pro 1803 (17134.345)
Version: master 5ab3311
```

For official builds:

```
**Bug description**
Game crushes on ENTER

**Steps to reproduce**
 1. Launch the game
 2. Press Enter

**System information**
OS: Windows 10 Pro 1803 (17134.345)
Version: 0.01a
```
## Creating feature request
If you want to create a good feature/enhancement request following:
- Avoid duplicates: Use search before submit!
- Check latest available build/version. Maybe this feature already exsist.
- One feature/enhancement per request
- State why this feature/enhancement should be created.
- Specify the name and version of the OS you're using.

### Feature/enhancement request example
For version build from github sources:

```
**Feature description**
Add support for quest tracking support

**Why**
This will make it easier to track in-game quests

**System information**
OS: Windows 10 Pro 1803 (17134.345)
Version: master 5ab3311
```

For official builds:

```
**Feature description**
Add support for quest tracking support

**Why**
This will make it easier to track in-game quests

**System information**
OS: Windows 10 Pro 1803 (17134.345)
Version: 0.01a
```

## Style guidelines for git commit messages
- Limit the first line to 72 characters or less
- Describe what you have done
- Reference issues and pull requests after the first line

## Style guidelines for code
- Use K&R C++ formating with 120 symbols margin.

```
#include <math.h>

class Point {
public:
	Point(double x, double y) :
			x(x), y(y) {
	}
	double distance(const Point& other) const;

	double x;
	double y;
};

double Point::distance(const Point& other) const {
	double dx = x - other.x;
	double dy = y - other.y;
	return sqrt(dx * dx + dy * dy);
}
```
