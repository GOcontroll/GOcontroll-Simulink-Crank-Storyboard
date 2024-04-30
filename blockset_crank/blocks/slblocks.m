%this function gets called when simulink opens(?) and sets up the library.

function blkStruct = slblocks

	Browser.Library = 'GOcontroll_Crank';

	Browser.Name = 'Crank Storyboard';

	blkStruct.Browser = Browser;

end