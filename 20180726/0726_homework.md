1. �������յ���ģʽ���÷�����������д����

2. ��дһ���࣬ʵ�ּ򵥵�ջ��ջ�������²�����
		   > Ԫ����ջ     void push(int);
		   > Ԫ�س�ջ     void pop();
		   > ����ջ��Ԫ�� int top();
		   > �ж�ջ��     bool emty();
		   > �ж�ջ��     bool full();
	 ���ջ�����������ֹ��ջ�����ݳ�Ա�ɴ��
	 10���������ݵ����鹹�ɡ��Ⱥ������²�����
	     > ����ջ
	     > ��10��ջ
	     > ��12��ջ
	     > ��14��ջ
	     > ���������ջ��Ԫ��
	     > ��ջ
	     > ���������ջ��Ԫ��

3. ��дһ���࣬ʵ�ּ򵥵Ķ��С������������²�����
       > Ԫ�����             void push(int);
       > Ԫ�س���             void pop();
       > ��ȡ��ͷԪ��         int front();
       > ��ȡ��βԪ��         int back();
       > �ж϶����Ƿ�Ϊ��     bool emty();
		   > �ж϶����Ƿ�����     bool full();
		   
4. �ڷ�װLinux�»���������������
    ������MutexLock����������Condition��Ŀ�����£�

   class MutexLock
   {
   public:
      //...
			void lock();
			void unlock();
	 private:
	 	  //...
   };

   class Condition
   {
   public:
      //...
			void wait();
			void notify();
			void notifyall();
	 private:
	    //...
   };