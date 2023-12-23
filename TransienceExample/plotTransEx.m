clear all;

run1 = 1;
run2 = 0;
run3i = 0;
run3f = 0;
run4 = 0;

xmin = 1.0;
xmax = 8.0;
fntsz = 13;
nvar = 16;
tint = 0.0001;

Dir1=[num2str(run1) '_' num2str(run2)];
for run3 = run3i:run3f
    
    Dir2=[Dir1 '_' num2str(run3)];
    Run=[Dir2 '_' num2str(run4)];
    locatn = ['data/'];
    
    run=[Run '_1'];
    VarN=[locatn 'V' run '.dat'];
    f1=fopen(VarN);
    yy1=fread(f1,[nvar, 10000000],'double')';
    fclose(f1);
    
    run=[Run '_2'];
    VarN=[locatn 'V' run '.dat'];
    f1=fopen(VarN);
    yy2=fread(f1,[nvar, 10000000],'double')';
    fclose(f1);
    
    run=[Run '_3'];
    VarN=[locatn 'V' run '.dat'];
    f1=fopen(VarN);
    yy3=fread(f1,[nvar, 10000000],'double')';
    fclose(f1);
    
    bs3a = load([locatn 'bursts1J' Run '_3.txt']);
    bs3b = load([locatn 'bursts2J' Run '_3.txt']);
    
    Va = [yy1(1:end-1,1); yy2(1:end-1,1); yy3(1:end-1,1)];
    if nvar<16
        Vb = [yy1(1:end-1,2); yy2(1:end-1,2); yy3(1:end-1,2)];
    else
        Vb = [yy1(1:end-1,8); yy2(1:end-1,8); yy3(1:end-1,8)];
    end
    t1 = 0.0;
    t2 = (length(yy1(:,1))-1)*tint;
    t3 = t2 + (length(yy2(:,1))-1)*tint;
    t4 = t3 + (length(yy3(:,1))-1)*tint;
    
    tt = t1:tint:t4;
    
    nbs = find(bs3a(:,2)>0.21);
    nb = nbs(1)-1;
    strtx = find(tt>0.07*(xmax-xmin)+xmin);
    xend = find(tt>xmax-0.07*(xmax-xmin));
    
    gmodE = [tt(strtx(1)) t2 t2 t3 t3 tt(xend(1))];
    gs = [0 0 1 1 0 0];
    
    f = figure();
    f.PaperPositionMode = 'manual';
    f.PaperUnits = 'inches';
    f.Units = 'inches';
    f.OuterPosition = [1 1 10 8];
    f.InnerPosition = [0.2 0.2 9.6 7.6];
    f.PaperPosition = [0.2 0.2 8.25 5.0];
    f.RendererMode = 'manual';

    axes('Position', [0.09, 0.81, 0.37, 0.19])
    rectangle('Position',[bs3b(2,1)+t3-0.05 -80 1.5 150],'FaceColor',[0.8 0.8 0.8],'LineStyle','none');
    hold on
    plot(tt(strtx(1):xend(1)-1),Vb(strtx(1):xend(1)-1),'color',[0 128 255]/255,'linewidth',1.5)
    text(xmin,10,'V_1','fontsize',fntsz,'fontweight','bold','fontname','arial')
    plot([xmax-0.05*(xmax-xmin) xmax-0.05*(xmax-xmin)], [-10 40],'k','linewidth',3)
    text(xmax-0.04*(xmax-xmin),15,'50 mV','fontsize',fntsz-2,'fontweight','bold','fontname','arial')
    plot([xmax-0.05*(xmax-xmin) xmax-0.04*(xmax-xmin)], [-30 -30],'k','linewidth',3)
    text(xmax-0.03*(xmax-xmin),-30,'-30 mV','fontsize',fntsz-2,'fontweight','bold','fontname','arial')
    xlim([xmin xmax])
    ylim([-80 70])
    axis off
    
    axes('Position', [0.09, 0.74, 0.37, 0.05])
    plot(gmodE,gs,'k','linewidth',1.5)
    hold on
    plot([t3+0.01*(xmax-xmin) t3+0.02*(xmax-xmin)], [1 1],'k','linewidth',3)
    text(t3+0.03*(xmax-xmin),1,'1 nS','fontsize',fntsz-2,'fontweight','bold','fontname','arial')
    text(xmin+0.01*(xmax-xmin),.8,'g_E','fontsize',fntsz,'fontweight','bold','fontname','arial')
    axis([xmin xmax 0 1.5])
    axis off
    
    axes('Position', [0.09, 0.53, 0.37, 0.19])
    rectangle('Position',[bs3b(2,1)+t3-0.05 -80 1.5 150],'FaceColor',[0.8 0.8 0.8],'LineStyle','none');
    hold on
    plot(tt(strtx(1):xend(1)-1),Va(strtx(1):xend(1)-1),'color',[255 128 0]/255,'linewidth',1.5)
    text(xmin,10,'V_2','fontsize',fntsz,'fontweight','bold','fontname','arial')
    plot([xmax-0.05*(xmax-xmin) xmax-0.05*(xmax-xmin)], [-10 40],'k','linewidth',3)
    text(xmax-0.04*(xmax-xmin),15,'50 mV','fontsize',fntsz-2,'fontweight','bold','fontname','arial')
    plot([xmax-0.05*(xmax-xmin) xmax-0.04*(xmax-xmin)], [-30 -30],'k','linewidth',3)
    text(xmax-0.03*(xmax-xmin),-30,'-30 mV','fontsize',fntsz-2,'fontweight','bold','fontname','arial')
    xlim([xmin xmax])
    ylim([-80 70])
    axis off
    
    axes('Position', [0.09, 0.46, 0.37, 0.05])
    plot(gmodE,gs,'k','linewidth',1.5)
    hold on
    plot([t3+0.01*(xmax-xmin) t3+0.02*(xmax-xmin)], [1 1],'k','linewidth',3)
    text(t3+0.03*(xmax-xmin),1,'1 nS','fontsize',fntsz-2,'fontweight','bold','fontname','arial')
    text(xmin+0.01*(xmax-xmin),.8,'g_{E}','fontsize',fntsz,'fontweight','bold','fontname','arial')
    axis([xmin xmax 0 1.5])
    axis off
    
    axes('Position', [0.09, 0.28, 0.37 0.14])
    rectangle('Position',[1000*(bs3b(2,1)+t3-0.05) 15 1500 485],'FaceColor',[0.8 0.8 0.8],'LineStyle','none');
    hold on
    plot(1000*(bs3a(:,1)+t3),bs3a(:,6)*1000,'.-','color',[255 128 0]/255,'markersize',10,'linewidth',1.5)
    plot(1000*(bs3b(:,1)+t3),bs3b(:,6)*1000,'.-','color',[0 128 255]/255,'markersize',10,'linewidth',1.5)
    xlim(1000*[xmin xmax])
    ax1 = gca;
    yticks([0 250 500]);
    xticks([]);
    ax1.LineWidth = 2.5;
    ax1.FontSize = fntsz-2;
    ax1.FontWeight = 'bold';
    ax1.FontName = 'arial';
    box off;
    ylabel('BD (ms)','fontsize',fntsz,'fontweight','bold','fontname','arial')
    
    axes('Position', [0.09, 0.1, 0.37, 0.14])
    rectangle('Position',[1000*(bs3b(2,1)+t3-0.05) 15 1500 485],'FaceColor',[0.8 0.8 0.8],'LineStyle','none');
    hold on
    plot(1000*(bs3a(:,1)+t3),bs3a(:,7)*1000,'.-','color',[255 128 0]/255,'markersize',10,'linewidth',1.5)
    plot(1000*(bs3b(:,1)+t3),bs3b(:,7)*1000,'.-','color',[0 128 255]/255,'markersize',10,'linewidth',1.5)
    xlim(1000*[xmin xmax]);
    ax1 = gca;
    ax1.LineWidth = 2.5;
    yticks([0 250 500]);
    ax1.FontSize = fntsz-2;
    ax1.FontWeight = 'bold';
    ax1.FontName = 'arial';
    box off;
    ylabel('IBI (ms)','fontsize',fntsz,'fontweight','bold','fontname','arial')
    xlabel('Time (ms)','fontsize',fntsz,'fontweight','bold','fontname','arial')

    xmin = 1000*(t3+0.1); 
    xmax = 1000*(bs3a(nb,1)+t3+0.15);   
    xl = xmax-xmin;
    
    xxa = 1000*(bs3a(2:nb,1)+0.5*bs3a(2:nb,6)+t3);
    xxb = 1000*(bs3b(2:nb,1)+0.5*bs3b(2:nb,6)+t3);
    p3a = polyfit(xxa,bs3a(2:nb,6)*1000,1);
    p3b = polyfit(xxb,bs3b(2:nb,6)*1000,1);
    pxxa = [xxa(1)-100; xxa; xxa(end)+100];
    pxxb = [xxb(1)-100; xxb; xxb(end)+100];
    
    ymin = 60;
    ymax = 110;
    yl = ymax-ymin;
    axes('Position', [0.64, 0.55, 0.35 0.35])
    plot(pxxa,p3a(1)*pxxa+p3a(2),'color',[255 178 102]/255,'linewidth',2)
    hold on
    plot(pxxb,p3b(1)*pxxb+p3b(2),'color',[102 178 255]/255,'linewidth',2)
    plot(xxa,bs3a(2:nb,6)*1000,'.-','color',[255 128 0]/255,'markersize',10,'linewidth',1.5)
    plot(xxb,bs3b(2:nb,6)*1000,'.-','color',[0 128 255]/255,'markersize',10,'linewidth',1.5)
    text(xmin+0.1*xl,ymax-0.14*yl,['Flexor slope_{BD} = ' num2str(p3a(1))],'fontsize',fntsz-2,...
        'fontweight','bold','fontname','arial','color',[255 128 0]/255);
    text(xmin+0.1*xl,ymax,['Extensor slope_{BD} = ' num2str(p3b(1))],'fontsize',fntsz-2,...
        'fontweight','bold','fontname','arial','color',[0 128 255]/255);
    ylabel('BD (ms)','fontsize',fntsz,'fontweight','bold','fontname','arial')
    xlim([xmin xmax]);
    ylim([ymin ymax]);
    box off;
    ax1 = gca;
    xticks([]);
    ax1.LineWidth = 2.5;
    ax1.FontSize = fntsz-2;
    ax1.FontWeight = 'bold';
    ax1.FontName = 'arial';
    
    p3ai = polyfit(xxa,bs3a(2:nb,7)*1000,1);
    p3bi = polyfit(xxb,bs3b(2:nb,7)*1000,1);
    
    ymin = 80;
    ymax = 130;
    yl = ymax-ymin;
    axes('Position', [0.64, 0.1, 0.35, 0.35]);
    hold on;
    plot(pxxa,p3ai(1)*pxxa+p3ai(2),'color',[255 178 102]/255,'linewidth',2)
    plot(pxxb,p3bi(1)*pxxb+p3bi(2),'color',[102 178 255]/255,'linewidth',2)
    plot(xxa,bs3a(2:nb,7)*1000,'.-','color',[255 128 0]/255,'markersize',10,'linewidth',1.5)
    plot(xxb,bs3b(2:nb,7)*1000,'.-','color',[0 128 255]/255,'markersize',10,'linewidth',1.5)
    text(xmin+0.1*xl,ymax-0.14*yl,['Flexor slope_{IBI} = ' num2str(p3ai(1))],'fontsize',fntsz-2,...
        'fontweight','bold','fontname','arial','color',[255 128 0]/255);
    text(xmin+0.1*xl,ymax,['Extensor slope_{IBI} = ' num2str(p3bi(1))],'fontsize',fntsz-2,...
        'fontweight','bold','fontname','arial','color',[0 128 255]/255);
    ylabel('IBI (ms)','fontsize',fntsz,'fontweight','bold','fontname','arial');
    xlabel('Time (ms)','fontsize',fntsz,'fontweight','bold','fontname','arial');
    xlim([xmin xmax]);
    ylim([ymin ymax]);
    box off;
    ax1 = gca;
    ax1.LineWidth = 2.5;
    ax1.FontSize = fntsz-2;
    ax1.FontWeight = 'bold';
    ax1.FontName = 'arial';

    print(f,['pTransEx' run '.eps'],'-depsc','-r0')
    close(f);    
end
