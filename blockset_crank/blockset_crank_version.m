%%***************************************************************************************
%% file         blockset_modbus_version.m
%% brief        Sets the blockset version in the simulink blocks
%%
%%---------------------------------------------------------------------------------------
%%                          C O P Y R I G H T
%%---------------------------------------------------------------------------------------
%%  Copyright 2024 (c) by GOcontroll     http://www.gocontroll.com    All rights reserved
%%
%%---------------------------------------------------------------------------------------
%%                            L I C E N S E
%%---------------------------------------------------------------------------------------
%% Permission is hereby granted, free of charge, to any person obtaining a copy of this
%% software and associated documentation files (the "Software"), to deal in the Software
%% without restriction, including without limitation the rights to use, copy, modify, merge,
%% publish, distribute, sublicense, and/or sell copies of the Software, and to permit
%% persons to whom the Software is furnished to do so, subject to the following conditions:
%%
%% The above copyright notice and this permission notice shall be included in all copies or
%% substantial portions of the Software.
%%
%% THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
%% INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
%% PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE
%% FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
%% OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
%% DEALINGS IN THE SOFTWARE.
%%
%%***************************************************************************************

function [version] = blockset_crank_version()

version = 'Crank v0.0.6';

%% V0.0.6 Update 30-4-2024
%% now compiles the mex files using a callback function of the block library
%% V0.0.5 Update 30-4-2024
%% the crank blockset is now useable via a standard matlab toolbox, only auto mex compilation is missing
%% 1.0.0 will be the first one actually published to the matlab file sharing platform
%%
%% V0.0.4 Update 17-4-2024
%% added a mechanism to automatically recompile the mex files when an update has happened.
%%
%% V0.0.3 Update 17-4-2024
%% added a channel name check length at compile time, to avoid possible runtime confusion
%% increased efficiency of event match by using a switch instead of a set of ifs
%% this does remove the ability to deserialize the event twice, but why would you do that?
%%
%% V0.0.2 Update 10-4-2024
%% fixed deserialize name number
%% fixed deserialize for events containing no data
%% fixed sample time for receive and serialize blocks
%% fixed event name matching in the receive block
%% fixed channels in receive and serialize
%% added example model