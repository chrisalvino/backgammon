
#ifndef DIE_H__
#define DIE_H__

namespace zeno {

    class Die {
    public:
    	Die();

    	virtual ~Die();

    	virtual int getDieRoll()=0;

    private:
    	Die(const Die &rhs);
    	
    	Die & operator=(const Die &rhs);	
    
    };

}

#endif // DIE_H__