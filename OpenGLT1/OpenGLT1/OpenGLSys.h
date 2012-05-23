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

	void SetProjection(int width, int height);
	void Prepare(float dt);
	void Render();
};
