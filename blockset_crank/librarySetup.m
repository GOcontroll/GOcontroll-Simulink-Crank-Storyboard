addpath([pwd]);
addpath([pwd filesep 'blocks']);

% compile mex files
d = dir('blocks');
files = {d.name};
for idx = 1:length(files)
	name = char(files(1,idx));
	if contains(name, ".c") && contains(name, "sfcn")
		[~, fname, ~] = fileparts(name);
		if exist(fname, "file") ~= 3
			mex(['blocks' filesep fname '.c'], '-outdir', 'blocks');
		end
	end
end