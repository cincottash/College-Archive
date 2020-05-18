h = 10.^(-(1:20));

fp = (exp(1+h)-exp(1))./h;

plot(-(1:20),fp,'go-')