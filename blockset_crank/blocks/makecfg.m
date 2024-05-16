%this file runs before the make command is invoked and allows for changes to it, so we can add our include folder and library
function makecfg(objBuildInfo)
	%$(START_DIR) is the folder the project is being built from, because the user must supply these files
	%this is the nicest places to make them put it all
	lib_path = fullfile('$(START_DIR)', 'crank_files');
	addIncludePaths(objBuildInfo,lib_path); %add the -I/path/to/includes to the makefile
	
	addLinkFlags(objBuildInfo,{'-ldl', ['-L' fullfile(lib_path)], '-lgreio'}); %add the library to the makefile
	% addDefines(objBuildInfo, '-DGRE_TARGET_OS_linux'); % worked without this define? Not sure if necessary, will be hard to make multiplatform.
	clear lib_path
end