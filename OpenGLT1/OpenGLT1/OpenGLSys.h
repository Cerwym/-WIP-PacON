


class OpenGLSys
{
private:
	int m_windowWidth;
	int m_windowHeight;

	GLfloat m_rotation;

public:
	OpenGLSys();
	virtual ~OpenGLSys();

	bool Init();
	bool Shutdown();

	bool SetProjection(int width, int height);

	void Enable2D();
	void Disable2D();
};