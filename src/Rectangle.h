class Rectangle
{
private:
	int x, y, w, h;
protected:
	int oldwidth, oldheight;
public:
	Rectangle(int x_pos, int y_pos, int width, int height)
					: x(x_pos)
					, y(y_pos)
					, w(width)
					, h(height) {}

	/* Retruns true if size changed */
	bool SetSize(int width, int height) {
		if(width != w || height != h){
			oldwidth = w;
			oldheight = h;
			w = width;
			h = height;
			return true;
		}
		return false;
	}
	/* Retruns true if position changed */
	bool SetPos(int x_pos, int y_pos) {
		if(x_pos != x || y_pos != y){
			x = x_pos;
			y = y_pos;
			return true;
		}
		return false;
	}
};
