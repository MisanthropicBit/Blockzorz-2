#ifndef BLOCKZORZ2_ANIMATION_HPP
#define BLOCKZORZ2_ANIMATION_HPP

class animation {
	public:
		animation();
        
		void animate(int dt);
		void play();
		void stop();

        void set_framerate(int framerate);
        void set_frame(int frame);
		void set_max_frames(int maxframes);
		void oscillate();
		void stop_oscillate();

        int current_frame() const;
		bool is_animating() const;

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
