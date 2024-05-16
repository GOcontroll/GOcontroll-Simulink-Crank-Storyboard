function events = processCrankHeader(file)

	events.names = string([]);
	events.fmts = string([]);
	events.num_fields = double([]);
	events.field_types = double([]);
	events.field_names = string([]);
	events.field_sizes = double([]);
	c_types = ["double","float","int8_t","uint8_t","int16_t","uint16_t","int32_t","uint32_t"];
	m_types = [ 0        1       2        3         4         5          6         7];
	type_map = containers.Map(c_types, m_types);
	lines = splitlines(file);
	lines = strtrim(lines); % flatten the file
	event_num = 0;
	i = 1;
	while i <= length(lines)
		if contains(lines(i),'EVENT')
			event_num = event_num + 1;
			events.names(event_num) = string(extractBetween(lines(i),'"','"'));
			events.fmts(event_num) = "";
			i = i + 1;
			field_num = 0;
			while  i <= length(lines) && ~contains(lines(i),'EVENT')
				if contains(lines(i),'FMT')
					events.fmts(event_num) = string(extractBetween(lines(i),'"','"'));
					i = i + 1;
					while ~contains(lines(i),'}') && i <= length(lines)
						split_line = split(lines(i));
						i = i + 1;
						try
							field_num = field_num + 1;
							events.field_types(event_num,field_num) = type_map(char(split_line(1)));
							nameAndSize = string(strip(split_line(2),'right', ';'));
							nameAndSizeSplit = split(nameAndSize, '[');
							events.field_names(event_num,field_num) = string(nameAndSizeSplit(1));
							try
								events.field_sizes(event_num, field_num) = str2double(strip(nameAndSizeSplit(2),'right', ']'));
							catch
								events.field_sizes(event_num, field_num) = 1;
							end
						catch
							field_num = field_num - 1;
						end
					end
				else
					i = i + 1;
				end
			end
			events.num_fields(event_num) = field_num;
		else
			i = i + 1;
		end
	end
end