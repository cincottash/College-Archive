clear all
%%
DEBoundary = delaware();
%1.  Translate the state of Delaware so that its center is approximately at the origin.
for c = 1:3
    new_DEBoundary{c} = DEBoundary{c} + [75.4505 ; -39.2]; %Translating the plot so that it's roughly in the origin
end
%Plotting all of the cells. 
plot(new_DEBoundary{1}(1,:),new_DEBoundary{1}(2,:), new_DEBoundary{2}(1,:),new_DEBoundary{2}(2,:), new_DEBoundary{3}(1,:),new_DEBoundary{3}(2,:));
pbaspect([1 1 1]);

%%
%2.  Dilate the translated state of Delaware so that it fits inside a square of side length one centered at the origin.
D1 = [4/3, 0;0, 3/4];
for c = 1:3
    new_DEBoundary{c} =  D1 * new_DEBoundary{c}; 
end
%Plotting all of the cells. 
plot(new_DEBoundary{1}(1,:),new_DEBoundary{1}(2,:), new_DEBoundary{2}(1,:),new_DEBoundary{2}(2,:), new_DEBoundary{3}(1,:),new_DEBoundary{3}(2,:));
pbaspect([1 1 1]);
%%

%3.  Rotate the translated, dilated state of Delaware so that New Castle County is at the bottom and Sussex is at the top
R = [-1, 0;0, -1]; 
for c = 1:3
    new_DEBoundary{c} = R * new_DEBoundary{c}; 
end
%Plotting all of the cells. 
plot(new_DEBoundary{1}(1,:),new_DEBoundary{1}(2,:), new_DEBoundary{2}(1,:),new_DEBoundary{2}(2,:), new_DEBoundary{3}(1,:),new_DEBoundary{3}(2,:));
pbaspect([1 1 1]);
%%

%4.  Dilate the translated, dilated, rotated state of Delaware without changing its area, so that it is about as wide as it is tall.
D2 = [3/2, 0;0, 2/3]; 
for c = 1:3
    new_DEBoundary{c} = D2 * new_DEBoundary{c}; 
end
%Plotting all of the cells. 
plot(new_DEBoundary{1}(1,:),new_DEBoundary{1}(2,:), new_DEBoundary{2}(1,:),new_DEBoundary{2}(2,:), new_DEBoundary{3}(1,:),new_DEBoundary{3}(2,:));
pbaspect([1 1 1]);
%%

%5.  Shear the translated, dilated, rotated, dilated state of Delaware so that the northernmost tip is atleast 2 units to the right of the southernmost tip.
SH = [1, 3;0, 1]; 
for c = 1:3
    new_DEBoundary{c} = SH * new_DEBoundary{c}; 
end

%Plotting all of the cells. 
plot(new_DEBoundary{1}(1,:),new_DEBoundary{1}(2,:), new_DEBoundary{2}(1,:),new_DEBoundary{2}(2,:), new_DEBoundary{3}(1,:),new_DEBoundary{3}(2,:));
pbaspect([1 1 1]);
%%

function Ss = Delaware()

q=kml_read('gz_2010_us_040_00_500k.kml');

idx = 485:487;

Ss = {};

    for j = idx
        Ss{end+1} = [ [q(j).X; q(j).X(1)]' ;[q(j).Y; q(j).Y(1)]' ];
    end
end