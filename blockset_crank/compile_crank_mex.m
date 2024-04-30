%get the path of this script so we can compile the mexes using it.
mfilePath = mfilename('fullpath');
if contains(mfilePath,'LiveEditorEvaluationHelper')
    mfilePath = matlab.desktop.editor.getActiveFilename;
end
%remove the filename from the end
[path, ~, ~] = fileparts(mfilePath);
% if sfcn_crank_version doesn't exist or the result of it is false, recompile the mex files
if ~(exist('crank_mex_version', "file") == 3) || ~crank_mex_version()
	% compile mex files
	% first compile version mex as it is not a level 2 s function
	mex(fullfile(path, 'blocks', 'crank_mex_version.c'), '-outdir',fullfile(path, 'blocks'), ['-DVERSION=''"' blockset_crank_version() '"''']) %jank quote stuff to get it into the define correctly
	d = dir(fullfile(path, 'blocks'));
	files = {d.name};
	for idx = 1:length(files)
		name = char(files(1,idx));
		if contains(name, ".c") && contains(name, "sfcn")
			[~, fname, ~] = fileparts(name);
			mex([path filesep 'blocks' filesep fname '.c'], '-outdir', fullfile(path, 'blocks'));
		end
	end
end
%cleanup
clear mfilePath path d files idx name fname