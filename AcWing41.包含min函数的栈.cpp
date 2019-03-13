class MinStack {
public:
    /** initialize your data structure here. */
    int arr[1000005];
    int mins[1000005];
    int a_t, a_e;
    MinStack() {
        memset(arr, 0, sizeof(arr));
        for(int i = 0; i < 1000005; i ++)
            mins[i] = 0x7fffffff;
        a_t = a_e = -1;
    }
    void push(int x) {
        arr[++ a_t] = x;
        if(a_t == 0)
        {
            mins[a_t] = min(mins[a_t], arr[a_t]);
        }
        else
        {
            mins[a_t] = min(arr[a_t], mins[a_t - 1]);
        }
    }
    void pop() {
        mins[a_t] = 0x7fffffff;
        a_t --;
    }
    int top() {
        return arr[a_t];
    }
    int getMin() {
        return mins[a_t];
    }
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack obj = new MinStack();
 * obj.push(x);
 * obj.pop();
 * int param_3 = obj.top();
 * int param_4 = obj.getMin();
 */
