# Changelog

## [Unreleased]

## [v0.0.1] - 2017-11-19
- Initial alpha version.

### Added
- Record module.

### Bugs
- Creates blank folders on C:\ root.


## [pre-alpha] - 2017-09-13 to 2017-11-18
### Summary
- Implement	Record Module
- Design	mapping of pixel values to vibration
- Design	consecutive detection counter threshold
- Design	factories to create new Modules
- Organize	modules in unique namespaces
- Implement	RealtimeControl Module placeholder
- Include	CSerial library
- Design	detection of Green/Yellow traffic lights
- Implement	RealtimeCapture Module placeholder
- Include	LibRealSense library
- Implement	placeholder Load/SaveConfig classes
- Include	LibConfig library
- Upgrade	project to VS2017
- Organize	modules to separate Modules project
- Implement	unit test for TrafficLight
- Design	histogram for depth detection
- Design	reverted from threads to sequential
- Implement	MainMenu Module
- Implement	Display Module
- Design	Input/Output/Parameters pattern
- Implement Params/Results classes
- Design	module parallel threading model
- Implement	SimulateControl Module
- Implement	SimulateCapture Module
- Implement Vision Module
- Implement	Core Module
- Implement	DepthObstacle Module
- Implement	TrafficLight Module
- Include	OpenCV library

### Added
- Refactored Menu into separate classes Simulate and Realtime.
- Reorganized project, renamed some files, added filters.
- Completed parameters rework for Control/TrafficLight, added Load/SaveConfig functions, cleaned up.
- Major rework, splitting Simulate and Realtime parameters into separate classes, derive from Base class.
- Implemented smart mapping of raw depth values to vibration ratios, parameters to weight height and limit range.
- Implemented consecutive counter in Result class for TrafficLight, with threshold params.
- Major architectural rework, moved to namespaces, base classes, factories.
- Converted creation of Capture/Control modules to Factory design pattern, moved to Base.cpp/h files.
- Implemented ModuleControl using CSerial Class, Realtime Control in Menu.
- Added detection of green and yellow traffic lights, simplified BlobDetectorMode function.
- Added Record Module, Realtime Capture to Menu, lots of TODOs, some cleanup.
- Forgot dll and lib for Realsense.
- Included Realsense2 SDK dependency, basic realtime Capture loop working.
- Renamed libconfig++.dll. Removed references to obsolete Data class, improved Load/SaveConfig.
- Added libconfig, template Load/SaveConfig. Only detect traffic lights in top half. Cleaned up TrafficLight code.
- Upgraded projects to VS2017, minor changes to TL unit test.
- Moved Module source files to Modules project folder, update include references.
- Moved modules into separate project for UT. Wrote multi-image TrafficLight unit test.
- Depth detection uses histogram to filter closest nth percentile; added HeadProtection mode, new parameters.
- Switched from Module Init() function to using Parametrized Constructor as it should be. Derived Detect from DetectBase.
- Added Code Map and Class Diagram from VS2017 Enterprise.
- Reorganized the project files a bit (Dependencies, TestData), added second project for Unit Tests.
- Added placeholders for DetectVehicle, DetectFace(MachineLearning), and ParseConfig from INI file.
- Consolidated IDetector and IModule, Interface using (Data, Params, Input, Output).
- Redid lost improvements in DepthObstacle.
- Working on DepthObstacleDetector region selection, added text SimControl output.
- Parametrized launch of Realtime/Simulate Modules, implemented Display threading, improved MainMenu.
- Added missing OpenCV and ucrtbased DLLs.
- Switched to global Data class in Core for Modules, working Display class for color AND depth images.
- Proper threading with Done and NewFrame flags, added load photo and basic Control simulation.
- Added Core, VisionParams, VisionResults. Applied Module/Detect/Simulate naming convention.
- Added video simulation loading from file, and processing in separate threads.
- Created StopSignDetector class, added interfaces IDetector, IDetectorParams and IDetectorResults.
- Added DepthObstacleDetector, restructured all files into one project.
- Improved StreetLight detection with 3 modes, added Parameters class.
- Added TrafficLightDetection project, exploration on generic images.
- Updated .gitignore.
- Added OpenCV Library.
- Created project.
- Initial commit.