#include "0905041_base.h"
// #include <cmath>



//create Sphere Object
class Sphere : public Object
{
    Point3D center;
    double radius;

    public:
    Sphere(Point3D center, double radius)
    {
        this->reference_point = center;
        this->radius = radius;
       
    }

    //draw sphere
    void draw()
    {
        std::cout << "Sphere" << std::endl;

        Point3D spherePoints[100][100];
        
        int stacks = 20;
        int slices = 20;

        double theta, phi;

        double x, y, z;

        //generate points
        for (int i = 0; i <= stacks; i++)
        {
            theta = (double)i / stacks * M_PI;
            for (int j = 0; j <= slices; j++)
            {
                phi = (double)j / slices * 2 * M_PI;
                x = radius * cos(theta) * cos(phi);
                y = radius * sin(theta);
                z = radius * cos(theta) * sin(phi);
                spherePoints[i][j] = Point3D(x, y, z);
                std::cout << x << " " << y << " " << z << std::endl;
            }
        }

        //draw sphere by generated points - upper and lower hemisphere

        for(int i = 0; i < stacks; i++)
        {
            
            for(int j = 0; j <= slices; j++)
            {
                glBegin(GL_QUADS);  
                glColor3f(color.b, color.g, color.r);

                glPushMatrix();
                {
                    glTranslatef(reference_point.x, reference_point.y, reference_point.z);

                    glBegin(GL_QUADS);
                    {
                        //upper hemisphere
                        
                        glVertex3f(spherePoints[i][j].x, spherePoints[i][j].y, spherePoints[i][j].z);
                        glVertex3f(spherePoints[i][j+1].x, spherePoints[i][j+1].y, spherePoints[i][j+1].z);
                        glVertex3f(spherePoints[i+1][j].x, spherePoints[i+1][j].y, spherePoints[i+1][j].z);
                        glVertex3f(spherePoints[i+1][j+1].x, spherePoints[i+1][j+1].y, spherePoints[i+1][j+1].z);


                        //lower hemisphere
                        
                        glVertex3f(spherePoints[i][j].x, spherePoints[i][j].y, -spherePoints[i][j].z);
                        glVertex3f(spherePoints[i][j+1].x, spherePoints[i][j+1].y, -spherePoints[i][j+1].z);
                        glVertex3f(spherePoints[i+1][j].x, spherePoints[i+1][j].y, -spherePoints[i+1][j].z);
                        glVertex3f(spherePoints[i+1][j+1].x, spherePoints[i+1][j+1].y, -spherePoints[i+1][j+1].z);
                        



                        

                    }


                }

            }
            
        }
        




    }
};

//create triangle Object
class Triangle : public Object
{
    Point3D p1, p2, p3;
    public:
    Triangle(Point3D p1, Point3D p2, Point3D p3)
    {
        this->p1 = p1;
        this->p2 = p2;
        this->p3 = p3;

        //set normal
        this->normal = (p2 - p1) ^ (p3 - p1);
        this->normal.normalize();

        
    }

    //draw triangle
    void draw()
    {
        std::cout << "Triangle" << std::endl;
        glBegin(GL_TRIANGLES);
        glColor3f(color.b, color.g, color.r);
        glVertex3f(p1.x, p1.y, p1.z);
        glVertex3f(p2.x, p2.y, p2.z);
        glVertex3f(p3.x, p3.y, p3.z);
        glEnd();
    }
};

//create Floor Object
class Floor : public Object
{
    int numTiles;
    public:
    Floor(double floorWidth, double tileWidth)
    {
        reference_point = (-floorWidth / 2, -floorWidth / 2, 0);
        normal = (0, 0, 1);
        length = tileWidth;
    }


    void setCoefficients(){
        coEfficients[0] = 0.3;
        coEfficients[1] = 0.2;
        coEfficients[2] = 0.1;
        coEfficients[3] = 0.4;
    }

    //set shine 
    void setShine(){
        this->shine = 1;
    }

    //draw floor
    void draw()
    {
        std::cout << "Floor" << std::endl;
        for(int i = 0; i < numTiles; i++)
        {
            for(int j = 0; j < numTiles; j++)
            {
                glBegin(GL_QUADS);
                glColor3f(color.b, color.g, color.r);
                glVertex3f(reference_point.x + i * length, reference_point.y + j * length, reference_point.z);
                glVertex3f(reference_point.x + i * length, reference_point.y + (j+1) * length, reference_point.z);
                glVertex3f(reference_point.x + (i + 1) * length, reference_point.y + j * length, reference_point.z + length);
                glVertex3f(reference_point.x + (i + 1) * length, reference_point.y + (j+1) * length, reference_point.z);
                glEnd();
            }
        }
    }


}

//create Light Object
class Light{
    Point3D position;
    Color color;

    public:
    Light(Point3D position, Color color)
    {
        this->position = position;
        this->color = color;
    }

    void draw()
    {
        std::cout << "Light" << std::endl;

        glBegin(GL_POINTS);
        glColor3f(color.b, color.g, color.r);
        glVertex3f(position.x, position.y, position.z);
        glEnd();


    }
};


//create Quadratic General Surface Object
class QuadraticGeneralSurface : public Object
{
    double A, B, C, D, E, F, G, H, I, J;
    double radius, width, height;

    public:
        //constructor
        QuadraticGeneralSurface(surfaceCoefficients surfaceCoeff[10], Vector3D ref, double radius, double width, double height)
            this->A = surfaceCoeff[0];
            this->B = surfaceCoeff[1];
            this->C = surfaceCoeff[2];
            this->D = surfaceCoeff[3];
            this->E = surfaceCoeff[4];
            this->F = surfaceCoeff[5];
            this->G = surfaceCoeff[6];
            this->H = surfaceCoeff[7];
            this->I = surfaceCoeff[8];
            this->J = surfaceCoeff[9];
            this->radius = radius;
            this->width = width;
            this->height = height;
            this->reference_point = ref;
            
        }

        //set Normal respective of point for Quadratic General Surface
        void setNormal(Vector3D point){
            double x = 2*A*point.x + D*point.y + E*point.z + G;
            double y = 2*B*point.y + D*point.x + F*point.z + H;
            double z = 2*C*point.z + E*point.x + F*point.y + I;
            this->normal = Vector3D(x, y, z);
            this->normal.normalize();
        }
};


        











