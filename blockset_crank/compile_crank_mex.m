%get the path of this script so we can compile the mexes using it.
mfilePath = mfilename('fullpath');
if contains(mfilePath,'LiveEditorEvaluationHelper')
    mfilePath = matlab.desktop.editor.getActiveFilename;
end
%remove the filename from the end
[path, ~, ~] = fileparts(mfilePath);
% if crank_mex_version doesn't exist or the result of it is false, recompile the mex files
if ~(exist('crank_mex_version', "file") == 3) || ~crank_mex_version()
	disp("Compiling Crank c mex functions...");
	% compile mex files
	d = dir(fullfile(path, 'blocks'));
	files = {d.name};
	for idx = 1:length(files)
		name = char(files(1,idx));
		if contains(name, ".c") && contains(name, "sfcn")
			[~, fname, ~] = fileparts(name);
			fprintf("\nCompiling %s\n", fname);
			mex([path filesep 'blocks' filesep fname '.c'], '-outdir', fullfile(path, 'blocks'));
			fprintf("Compiled %s\n", fname);
		end
	end
	fprintf("\nCompiling crank_mex_version\n");
	mex(fullfile(path, 'blocks', 'crank_mex_version.c'), '-outdir',fullfile(path, 'blocks'), ['-DVERSION="' blockset_crank_version() '"'])
	disp("Finished compiling Crank c mex functions!");
end
%cleanup
clear mfilePath path d files idx name fname