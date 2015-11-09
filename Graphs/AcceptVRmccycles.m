close all
clear all
clc

%Import data and define closed-form solution
%Data for ordered spins (up = 1) and T = 1.0
filename = 'DataForGraphsC.xlsx';
sheet = 1;
xlRange = 'A6:D12';

[v,T,vT] = xlsread(filename, sheet, xlRange);
MCcycles=v(:,1); 
Accept_ordered_1=v(:,4);

%Data for ordered spins (up = 1) and T = 2.4
filename = 'DataForGraphsC.xlsx';
sheet = 2;
xlRange = 'A6:D12';

[v,T,vT] = xlsread(filename, sheet, xlRange);
Accept_ordered_2_4=v(:,4);

%Data for random spins and T = 1.0
filename = 'DataForGraphsC.xlsx';
sheet = 3;
xlRange = 'A6:D12';

[v,T,vT] = xlsread(filename, sheet, xlRange); 
Accept_random_1=v(:,4);

%Data for random spins and T = 2.4
filename = 'DataForGraphsC.xlsx';
sheet = 4;
xlRange = 'A6:D12';

[v,T,vT] = xlsread(filename, sheet, xlRange);
MCcycles=v(:,1); 
Accept_random_2_4=v(:,4);

%Plot data
%Accepted moves, T = 1.0, plot ordered + random
figure
semilogx(MCcycles,Accept_ordered_1,'-.b',MCcycles,Accept_random_1,'m','LineWidth',2)
legend('Ordered spins (up), T = 1.0','Random spins, T = 1.0','FontSize',12)

xlabel('Number of Monte Carlo cycles','FontSize',12)
ylabel('Accepted configurations','FontSize',12)

%ylim([20 300000])
xlim([0 10000])

%Accepted moves, T = 2.4, plot ordered + random
figure
semilogx(MCcycles,Accept_ordered_2_4,'-g',MCcycles,Accept_random_2_4,'--k','LineWidth',2)
legend('Ordered spins (up), T = 2.4','Random spins, T = 2.4','FontSize',12)

xlabel('Number of Monte Carlo cycles','FontSize',12)
ylabel('Accepted configurations','FontSize',12)

%ylim([8000 110000000])
xlim([0 10000])

%Accepted moves, T = 1 + 2.4, plot ordered
figure
semilogx(MCcycles,Accept_ordered_1,'-.b',MCcycles,Accept_ordered_2_4,'-g','LineWidth',2)
legend('Ordered spins (up), T = 1.0','Ordered spins (up), T = 2.4','FontSize',12)

xlabel('Number of Monte Carlo cycles','FontSize',12)
ylabel('Accepted configurations','FontSize',12)

%ylim([20 110000000])
xlim([0 10000])

%Accepted moves, T = 1 + 2.4, plot random
figure
semilogx(MCcycles,Accept_random_1,'m',MCcycles,Accept_random_2_4,'--k','LineWidth',2)
legend('Random spins, T = 1.0','Random spins, T = 2.4','FontSize',12)

xlabel('Number of Monte Carlo cycles','FontSize',12)
ylabel('Accepted configurations','FontSize',12)

%ylim([20 110000000])
xlim([0 10000])

