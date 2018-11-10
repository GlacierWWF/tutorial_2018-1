function my_pid(kp,ki,kd)
ts = 0.001;
sys = tf(5.235e5,[1,87.35,10470,0]);
dsys = c2d(sys,ts,'z'); %将连续系统传递函数转换为离散的
[num,den]=tfdata(dsys,'v');
u_1=0;
u_2=0;
u_3=0;
y_1=0;
y_2=0;
y_3=0;
x = [0,0,0]';
e_1 = 0;
u_max = 6;
for k=1:1:2000
   time(k) = k*ts;  %时间轴
   dst_u(k) = 20;   %输入的目标值  
   u(k) = kp*x(1)+kd*x(2)+ki*x(3);  %PID的输出
   
   %判断输出是否超过限定值
   if(u(k)>=u_max)
       u(k)=u_max;  
   end
   if(u(k)<=-u_max)
       u(k)=-u_max;
   end
   
   sys_out(k) = -den(2)*y_1-den(3)*y_2-den(4)*y_3+num(2)*u_1+num(3)*u_2...
       +num(4)*u_3; %系统的输出
   e(k) = dst_u(k) - sys_out(k);
   a = 1;
   %抗积分饱和
   if(u(k)>=u_max)
       if(e(k)>0)
           a = 0;
       else a = 1; end
   elseif(u(k)<=-u_max)
       if(e(k)>0)
           a = 1;
       else a = 0;
       end
   end
   
   u_3 = u_2;
   u_2 = u_1;
   u_1 = u(k);
   y_3 = y_2;
   y_2 = y_1;
   y_1 = sys_out(k);
   x(1) = dst_u(k) - sys_out(k);    %比例项
   x(2) = (e(k)-e_1)/ts;            %微分项
   x(3) = x(3) + a*e(k)*ts;         %积分项
   e_1 = e(k);
end
plot(time,dst_u,'r--',time,sys_out,'b');
xlabel('time');
ylabel('out');
legend('Ideal','actual');

end

  