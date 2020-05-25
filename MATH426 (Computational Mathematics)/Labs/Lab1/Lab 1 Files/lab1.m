DEBoundary = delaware2();
massBoundary = massachusetts();
newmassBoundary = massBoundary;
delCentered = DEBoundary;

massCenterVector = [72;-42];
massSquishVector = [0;-0.2];
dilation2Mat = [1 0;0 2.1];
elevationVec = [0;-0.2];
squishMat = [0.25 0; 0 1];
extendMat = [1.3 0;0 1];
shrinkMat = [0.95 0;0 1];
shiftRight = [0.05;0];

for k=1:9
    newmassBoundary{k} = newmassBoundary{k} + massCenterVector;
    newmassBoundary{k} = newmassBoundary{k} + massSquishVector;
    newmassBoundary{k} = dilation2Mat * newmassBoundary{k};
    newmassBoundary{k} = newmassBoundary{k} + elevationVec;
    newmassBoundary{k} = squishMat * newmassBoundary{k};
    newmassBoundary{k} = extendMat * newmassBoundary{k};
    newmassBoundary{k} = shrinkMat * newmassBoundary{k};
    newmassBoundary{k} = newmassBoundary{k} + shiftRight;
end
for d=1:3
    plot(delCentered{d}(1,:),delCentered{d}(2,:));
    pbaspect([1 1 1]);
    hold on
end
for j=1:9
    plot(newmassBoundary{j}(1,:),newmassBoundary{j}(2,:));
    pbaspect([1 1 1]);
end
hold off
