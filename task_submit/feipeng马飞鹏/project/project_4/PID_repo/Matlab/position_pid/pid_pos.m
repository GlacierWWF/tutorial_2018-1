function pid_pos(kp,ki,kd)
ts = 0.001;
xk = zeros(2,1);
last_e = 0; %记录的前一次的误差
last_u = 0; %记录的前一次的输出值
ie = 0;
for k=1:1:2000
   time(k) = k*ts;  %时间轴
   dst_u(k) = 0.5*sin(2*pi*k*ts);   %输入的目标值
   
   %求解传递函数
   para=last_u; %上一次PID输出的值作为这次的输入量
   tSpan = [0 ts];
   [tt,xx] = ode45('tf_function',tSpan,xk,[],para);
   xk = xx(length(xx),:);
   out_u(k) = xk(1); %PID控制器的输出值
   
   e(k) = dst_u(k) - out_u(k);  %比例项
   de(k) = (e(k)-last_e)/ts;    %微分项
   ie = ie + e(k);              %积分项
   
   u(k)=kp*e(k)+kd*de(k)+ki*ie; %位置式PID的计算公式
   
   last_u = u(k);               
   last_e = e(k);
end
plot(time,dst_u,'r--',time,out_u,'b');
xlabel('time');
ylabel('out');
legend('Ideal','actual');

end


  