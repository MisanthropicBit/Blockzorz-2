#ifndef ANIMATION_H
#define ANIMATION_H

class Animation
{
	public:
		Animation();
        
		void Animate(int dt);
		void Play();
		void Stop();

        void SetFrameRate(int framerate);
        void SetCurrentFrame(int frame);
		void SetMaxFrames(int maxframes);
		void Oscillate();
		void DontOscillate();

        int GetCurrentFrame() const;
		bool IsAnimating() const;

    private:
		int frame;
        int frameinc;
        int framerate;
        int maxframes;
		int timeleft;
        bool oscillate;
		bool animate;
};

#endif
