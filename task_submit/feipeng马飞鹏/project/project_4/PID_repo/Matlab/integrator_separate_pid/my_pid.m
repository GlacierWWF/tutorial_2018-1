function my_pid(kp,ki,kd)
limit = 5;
ts = 0.001;
xk = zeros(2,1);
last_e = 0; %��¼��ǰһ�ε����
last_u = 0; %��¼��ǰһ�ε����ֵ
ie = 0;
for k=1:1:2000
   time(k) = k*ts;  %ʱ����
   dst_u(k) = 20;   %�����Ŀ��ֵ
   
   %��⴫�ݺ���
   para=last_u; %��һ��PID�����ֵ��Ϊ��ε�������
   tSpan = [0 ts];
   [tt,xx] = ode45('tf_function',tSpan,xk,[],para);
   xk = xx(length(xx),:);
   out_u(k) = xk(1); %PID�����������ֵ
   
   e(k) = dst_u(k) - out_u(k);  %������
   
   de(k) = (e(k)-last_e)/ts;    %΢����
   ie = ie + e(k);              %������
   if(abs(e(k))>limit)
       u(k)=kp*e(k)+kd*de(k);
   end
   if(abs(e(k))<=limit)
       u(k)=kp*e(k)+kd*de(k)+ki*ie;
   end
   last_u = u(k);               
   last_e = e(k);
end
plot(time,dst_u,'r--',time,out_u,'b');
xlabel('time');
ylabel('out');
legend('Ideal','actual');

end

  