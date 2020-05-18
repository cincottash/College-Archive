function Ss = Delaware()

q=kml_read('gz_2010_us_040_00_500k.kml');

idx = 485:487;

Ss = {};
for j = idx
    Ss{end+1} = [ [q(j).X; q(j).X(1)]';[q(j).Y; q(j).Y(1)]' ];
end