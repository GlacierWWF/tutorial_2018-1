function out = tf_function(t,y,flag,para)
    u = para;
    J = 0.0067;
    B = 0.1;
    out = zeros(2,1);
    out(1) = y(2);
    out(2) = -(B/J)*y(2)+(1/J)*u;
    


end