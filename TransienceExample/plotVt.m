clear all;

run1 = 1; %Numbers used in your data file name
run2 = 0;
run3 = 0;
run4 = 0;

pul = 1; %Set to 1 if a pulse was applied, set to 0 if not
xmin = 0.0; %Beginning of time range that you want to look at
xmax = 11.0; %End of time range
tint = 0.0001; %Time step between data points
fntsz = 14; %Font size
nvar = 16; %Number of variables saved in your data file

dir2 = [num2str(run1) '_' num2str(run2) '_' num2str(run3)];
dir3 = [dir2 '_' num2str(run4)];
locatn = ['data/'];  %Location where your data is

if pul == 0  %If there is no pulse, only read from this one data file.
    VarN=[locatn 'V' dir3 '_0.dat'];
    f1=fopen(VarN);
    yy1=fread(f1,[16, 10000000],'double')';
    fclose(f1);
        
    V1 = yy1(:,1);  %Voltage data for neuron 1
    V2 = yy1(:,8);  %Voltage data for neuron 2

    t1 = tint*(length(yy1(:,1))-1); %Time duration of data
else         %If there is a pulse, concatenate 3 data files. 
    VarN=[locatn 'V' dir3 '_1.dat'];
    f1=fopen(VarN);
    yy1=fread(f1,[nvar, 10000000],'double')';
    fclose(f1);
    
    VarN=[locatn 'V' dir3 '_2.dat'];
    f1=fopen(VarN);
    yy2=fread(f1,[nvar, 10000000],'double')';
    fclose(f1);
    
    VarN=[locatn 'V' dir3 '_3.dat'];
    f1=fopen(VarN);
    yy3=fread(f1,[nvar, 10000000],'double')';
    fclose(f1);
       
    V1 = [yy1(1:end-1,1); yy2(1:end-1,1); yy3(:,1)];  %Voltage data for neuron 1
    V2 = [yy1(1:end-1,8); yy2(1:end-1,8); yy3(:,8)];  %Voltage data for neuron 2

    t1 = tint*(length(yy1(:,1))-1);  %Time duration of data file before the pulse
    t2 = t1 + tint*(length(yy2(:,1))-1); %Time duration from beginning of integration
                                         %to the end of the pulse
end

lnt = length(V1);   %Number of time points
tt = 0:tint:tint*(lnt-1);  %Time array

f = figure();
f.PaperPositionMode = 'manual';
f.PaperUnits = 'inches';
f.Units = 'inches';
f.OuterPosition = [1 1 9 5];
f.InnerPosition = [0.2 0.2 8.6 4.6];
f.PaperPosition = [0.2 0.2 7.0 3.0];
f.RendererMode = 'manual';

ymin = -80;  %Minimum of y-axis range
ymax = 50;  %Maximum of y-axis range
yl = ymax-ymin;  %Height of y-axis

axes('position',[0.11 0.55 0.85 0.35]);
hold on;
if pul
    rectangle('position',[t1 ymin+2 t2-t1 yl-2],'FaceColor',[0.7 0.7 0.7],...
                'EdgeColor','none');
end
plot(tt, V1,'k','linewidth',1.5);  %Plot voltage of neuron 1 versus time.
xlim([xmin xmax]);  %Set x axis range.
ylim([ymin ymax]);    %Set y axis range.
ylabel('V_1 (mV)','fontname','Arial','fontsize',fntsz,'fontweight','bold');
box off;
ax1 = gca;
ax1.LineWidth = 2.5;
ax1.FontName = 'Arial';
ax1.FontSize = fntsz-2;
ax1.FontWeight = 'bold';
ax1.XTick = [];

axes('position',[0.11 0.15 0.85 0.35]);
hold on;
if pul
    rectangle('position',[t1 ymin+2 t2-t1 yl-2],'FaceColor',[0.7 0.7 0.7],...
                'EdgeColor','none');
end
plot(tt, V2,'k','linewidth',1.5);  %Plot voltage of neuron 2 versus time.
xlim([xmin xmax]);
ylim([ymin ymax]);
ylabel('V_2 (mV)','fontname','Arial','fontsize',fntsz,'fontweight','bold');
xlabel('Time (s)','fontname','Arial','fontsize',fntsz,'fontweight','bold');
box off;
ax1 = gca;
ax1.LineWidth = 2.5;
ax1.FontName = 'Arial';
ax1.FontSize = fntsz-2;
ax1.FontWeight = 'bold';

print(f,['pV' dir3 '_3.eps'],'-depsc','-r0');
% close(f);
