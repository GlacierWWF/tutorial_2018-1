function my_pid(kp,ki,kd)
ts = 0.001;
xk = zeros(2,1);
last_e = 0; %��¼��ǰһ�ε����
last_u = 0; %��¼��ǰһ�ε����ֵ
e_1 = 0;
e_2 = 0;
e_3 = 0;
u_1 = 0;
for k=1:1:2000
   time(k) = k*ts;  %ʱ����
   dst_u(k) =20.0;
   %0.5*sin(2*pi*k*ts);   %�����Ŀ��ֵ
   
   %��⴫�ݺ���
   para=last_u; %��һ��PID�����ֵ��Ϊ��ε�������
   tSpan = [0 ts];
   [tt,xx] = ode45('tf_function',tSpan,xk,[],para);
   xk = xx(length(xx),:);
   out_u(k) = xk(1); %PID�����������ֵ
   
   e(k) = dst_u(k) - out_u(k);  %������
   de(k) = (e(k)-last_e)/ts;    %΢����
   ie = ie + e(k);              %������
   
   u(k)=kp*(e(k)-e_1)+kd*(e(k)-2*e_1+e_2)+ki*e(k); %λ��ʽPID�ļ��㹫ʽ
   
   e_2 = e_1;
   e_1 = e(k);
   last_u = u(k)+u_1;
   u_1 = last_u;
end
plot(time,dst_u,'r--',time,out_u,'b');
xlabel('time');
ylabel('out');
legend('Ideal','actual');

end


  