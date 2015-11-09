close all
clear all
clc

%Import data and define closed-form solution
%Data for ordered spins (up = 1) and T = 1.0
filename = 'DataForGraphsC.xlsx';
sheet = 1;
xlRange = 'A6:C12';

[v,T,vT] = xlsread(filename, sheet, xlRange);
MCcycles=v(:,1); 
MeanEnergyOrderedSpin_1=v(:,2);
MeanMagnetizationOrderedSpin_1=v(:,3);

%Data for ordered spins (up = 1) and T = 2.4
filename = 'DataForGraphsC.xlsx';
sheet = 2;
xlRange = 'A6:C12';

[v,T,vT] = xlsread(filename, sheet, xlRange);
MeanEnergyOrderedSpin_2_4=v(:,2);
MeanMagnetizationOrderedSpin_2_4=v(:,3);

%Data for random spins and T = 1.0
filename = 'DataForGraphsC.xlsx';
sheet = 3;
xlRange = 'A6:C12';

[v,T,vT] = xlsread(filename, sheet, xlRange);
MeanEnergyRandomSpin_1=v(:,2);
MeanMagnetizationRandomSpin_1=v(:,3);

%Data for random spins and T = 2.4
filename = 'DataForGraphsC.xlsx';
sheet = 4;
xlRange = 'A6:C12';

[v,T,vT] = xlsread(filename, sheet, xlRange);
MeanEnergyRandomSpin_2_4=v(:,2);
MeanMagnetizationRandomSpin_2_4=v(:,3);

%Plot data
%Mean energy, T = 1.0, plot ordered + random
figure
semilogx(MCcycles,-MeanEnergyOrderedSpin_1,'-.b',MCcycles,-MeanEnergyRandomSpin_1,'m','LineWidth',2)
legend('Ordered spins (up), T = 1.0','Random spins, T = 1.0','FontSize',12)

xlabel('Number of Monte Carlo cycles','FontSize',12)
ylabel('Absolute value of mean energy','FontSize',12)

ylim([730 820])

%Mean magnetization, T = 1.0, plot ordered + random
figure
semilogx(MCcycles,MeanMagnetizationOrderedSpin_1,'-.b',MCcycles,MeanMagnetizationRandomSpin_1,'m','LineWidth',2)
legend('Ordered spins (up), T = 1.0','Random spins, T = 1.0','FontSize',12)

xlabel('Number of Monte Carlo cycles','FontSize',12)
ylabel('Mean magnetization','FontSize',12)

ylim([300 430])

%Mean energy, T = 2.4, plot ordered + random
figure
semilogx(MCcycles,-MeanEnergyOrderedSpin_2_4,'-g',MCcycles,-MeanEnergyRandomSpin_2_4,'--k','LineWidth',2)
legend('Ordered spins (up), T = 2.4','Random spins, T = 2.4','FontSize',12)

xlabel('Number of Monte Carlo cycles','FontSize',12)
ylabel('Absolute value of mean energy','FontSize',12)

ylim([460 570])

%Mean magnetization, T = 2.4, plot ordered + random
figure
semilogx(MCcycles,MeanMagnetizationOrderedSpin_2_4,'-g',MCcycles,MeanMagnetizationRandomSpin_2_4,'--k','LineWidth',2)
legend('Ordered spins (up), T = 2.4','Random spins, T = 2.4','FontSize',12)

xlabel('Number of Monte Carlo cycles','FontSize',12)
ylabel('Mean magnetization','FontSize',12)

ylim([110 300])

