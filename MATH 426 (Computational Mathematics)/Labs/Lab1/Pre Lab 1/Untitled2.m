clear all

DEBoundary = delaware();
%1.  Translate the state of Delaware so that its center is approximately at the origin.
for c = 1:3
    DEBoundary{c} = DEBoundary{c} + [75.5505 ; -39.2]; %Translating the plot so that it's roughly in the origin
end

%2.  Dilate the translated state of Delaware so that it fits inside a square of side length one centered at the origin.
%D is our dilation matrix to make DE fit inside a 1x1 square.
%The resulting size of DE is about 0.9 x 0.9
D1 = [4/3;3/4];
for c = 1:3
    DEBoundary{c} = D1.* DEBoundary{c}; 
end

%3.  Rotate the translated, dilated state of Delaware so that New Castle County is at the bottom and Sussex is at the top
R = [1; -1]; %Flipping the y axis... I had to google where those locations were in DE.
for c = 1:3
    DEBoundary{c} = R.* DEBoundary{c}; 
end

%4.  Dilate the translated, dilated, rotated state of Delaware without changing its area, so that it is about as wide as it is tall.
D2 = [1;1]; %my shape is already almost the same size on the x and y axis so I just multilied by 1 to keep the original matrix
for c = 1:3
    DEBoundary{c} = D2.* DEBoundary{c}; 
end

%5.  Shear the translated, dilated, rotated, dilated state of Delaware so that the northernmost tip is atleast 2 units to the right of the southernmost tip.
SH = [3;1]; 
for c = 1:3
    DEBoundary{c} = SH.* DEBoundary{c}; 
end
%Plotting all of the cells. 
plot(DEBoundary{1}(1,:),DEBoundary{1}(2,:), DEBoundary{2}(1,:),DEBoundary{2}(2,:), DEBoundary{3}(1,:),DEBoundary{3}(2,:));
pbaspect([1 1 1]);


function Ss = Delaware()

q=kml_read('gz_2010_us_040_00_500k.kml');

idx = 485:487;

Ss = {};

    for j = idx
        Ss{end+1} = [ [q(j).X; q(j).X(1)]' ;[q(j).Y; q(j).Y(1)]' ];
    end
end