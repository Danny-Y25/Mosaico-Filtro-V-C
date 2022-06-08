
#include "cabezera.hpp"
Mat frame;
Mat nueva;
Mat anterior;
Mat anterior2;
Mat resta;
Mat resta2;
Mat parte;
Mat parte2;
Mat copiarGB;
int num1;
int valor = 0;
int colsImagen = 77;
int rowsImagen = 20;
Mat color;
Proyecto pro;

void eventoTrack(int v, void *data)

{
    // cout << valor << endl;
}

float Proyecto::promedioFrame(int colum, int fila)
{
    //cout<<colum<<" filas "<<fila<<endl;
    int longitudcolumn = colum + 25;
    int longitudfilas = fila + 25;
    int contfun = 0;
    float contrast = 0;

    for (int j = fila; j < longitudfilas; j++)

    {

        for (int i = colum; i < longitudcolumn; i++)
        {

            int pixel = nueva.at<uchar>(j, i);
            contfun = contfun + pixel;
        }
    }

    int promediofun = contfun / (25 * 25);

    if (promediofun >= 0 && promediofun <= 17)
    {
        contrast = 0.10;
    }
    if (promediofun >= 18 && promediofun <= 34)
    {
        contrast = 0.20;
    }

    if (promediofun >= 35 && promediofun <= 51)
    {
        contrast = 0.30;
    }

    if (promediofun >= 52 && promediofun <= 68)
    {
        contrast = 0.40;
    }

    if (promediofun >= 69 && promediofun <= 85)
    {
        contrast = 0.50;
    }

    if (promediofun >= 86 && promediofun <= 102)
    {
        contrast = 0.60;
    }

    if (promediofun >= 103 && promediofun <= 119)
    {
        contrast = 0.70;
    }

    if (promediofun >= 120 && promediofun <= 136)
    {
        contrast = 0.80;
    }

    if (promediofun >= 137 && promediofun <= 153)
    {
        contrast = 0.90;
    }

    if (promediofun >= 154 && promediofun <= 170)
    {
        contrast = 1.0;
    }

    if (promediofun >= 171 && promediofun <= 187)
    {
        contrast = 1.10;
    }

    if (promediofun >= 188 && promediofun <= 204)
    {
        contrast = 1.20;
    }

    if (promediofun >= 205 && promediofun <= 221)
    {
        contrast = 1.30;
    }
    if (promediofun >= 222 && promediofun <= 238)
    {
        contrast = 1.40;
    }

    if (promediofun >= 239 && promediofun <= 255)
    {
        contrast = 1.50;
    }

    //cout<< contrast<<" promedio "<< promediofun<<endl;

    return contrast;
}

void Proyecto::principal()
{

    // Captura de Video
    std::vector<String> datos;
    VideoCapture video("/dev/video0", CAP_V4L2);
    //VideoCapture video("Italia.mp4");
    if (video.isOpened())
    {
        namedWindow("Video", WINDOW_AUTOSIZE);

        string name = "./imagenes";

        int frame_width = video.get(cv::CAP_PROP_FRAME_WIDTH);

	    int frame_height = video.get(cv::CAP_PROP_FRAME_HEIGHT);

        int frame_widthEfecto = 1050;

	    int frame_heightEfecto = 1050;
        for (const auto &file : fs::recursive_directory_iterator(name))
        {
            string fileNmae = file.path();
            //cout<<file.path()<<endl;
            datos.push_back(fileNmae);
        }

        int imagencont = 1;
        VideoWriter videoGrabado("videoGrabado.avi", cv::VideoWriter::fourcc('M','J','P','G'), 10, Size(frame_width,frame_height));
        VideoWriter videoEfecto("videoEfecto.avi", cv::VideoWriter::fourcc('M','J','P','G'), 10, Size(frame_widthEfecto,frame_heightEfecto));

        while (3 == 3)
        {
            video >> frame;
            videoGrabado.write(frame);

            if (frame.empty())
            {
                break;
            }

            cvtColor(frame, nueva, COLOR_BGR2GRAY);
            resize(nueva, resta, Size(25, 25));
            resize(frame, color, Size(25, 25));
            resize(nueva, nueva, Size(1050, 1050), frame.type());

            if (valor == 0)
            {
                anterior = Mat::zeros(nueva.size(), nueva.type());
            }

            if (valor == 1 || valor == 2 || valor == 3 || valor == 4)
            {
                anterior = Mat::zeros(nueva.size(), frame.type());
            }
            

            int r = 0;
            int nume = 0;

            int gurda3 = 0;
            int gurda4 = 0;

            float alpha = 1.5; //contraste menor contraste mas oscura la imagen
            float beta = 0;    //brilo

            int sumapixles = 0;
            int promedio = 0;

            if (valor == 0)
            {
                // colsImagen = 77;
                rowsImagen = 41;
            }

            if (valor == 1 || valor == 2 || valor == 3 || valor == 4)
            {
                // colsImagen = 26;
                rowsImagen = 41;
            }

            for (int nume2 = 0; nume2 < rowsImagen; nume2++)

            {

                int c = 0;
                int gurda = 0;
                int gurda2 = 0;

                if (valor == 0)
                {
                    colsImagen = 77;
                }

                if (valor == 1 || valor == 2 || valor == 3 || valor == 4)
                {
                    colsImagen = 77;
                }

                for (int nume = 0; nume < colsImagen; nume++)

                {

                    alpha = pro.promedioFrame(c, r);

                    if (imagencont > 1000)
                    {
                        imagencont = 0;
                    }

                    string pa = datos[imagencont];

                    for (int j = 0; j < resta.rows; j++)

                    {

                        for (int i = 0; i < resta.cols; i++)

                        {
                            //

                            //
                            int pixel = resta.at<uchar>(j, i);
                            int pixelb = color.at<Vec3b>(j, i)[0];
                            int pixelg = color.at<Vec3b>(j, i)[1];
                            int pixelr = color.at<Vec3b>(j, i)[2];
                            if (valor == 0)
                            {
                                anterior.at<uchar>(r, c) = saturate_cast<uchar>(pixel * alpha + beta);
                            }

                            if (valor == 1)
                            {
                                anterior.at<Vec3b>(r, c)[0] = saturate_cast<uchar>(pixel * alpha + beta);
                            }
                            if (valor == 2)
                            {
                                anterior.at<Vec3b>(r, c)[1] = saturate_cast<uchar>(pixel * alpha + beta);
                            }
                            if (valor == 3)
                            {
                                anterior.at<Vec3b>(r, c)[2] = saturate_cast<uchar>(pixel * alpha + beta);
                            }
                            if (valor == 4)
                            {
                                
                                anterior.at<Vec3b>(r, c)[0] = saturate_cast<uchar>(pixelb * alpha + beta);
                                anterior.at<Vec3b>(r, c)[1] = saturate_cast<uchar>(pixelg * alpha + beta);
                                anterior.at<Vec3b>(r, c)[2] = saturate_cast<uchar>(pixelr * alpha + beta);
                            }
                            if (valor == 5)
                            {
                                
                                anterior.at<Vec3b>(r, c)[0] = saturate_cast<uchar>(pixelb * alpha + beta);
                                anterior.at<Vec3b>(r, c)[1] = pixelg; //saturate_cast<uchar>(pixelg * alpha + beta);
                                anterior.at<Vec3b>(r, c)[2] = pixelr; //saturate_cast<uchar>(pixelr * alpha + beta);
                            }
                            if (valor == 6)
                            {
                                
                                anterior.at<Vec3b>(r, c)[0] = pixelb;//saturate_cast<uchar>(pixelb * alpha + beta);
                                anterior.at<Vec3b>(r, c)[1] = saturate_cast<uchar>(pixelg * alpha + beta);
                                anterior.at<Vec3b>(r, c)[2] = pixelr; //saturate_cast<uchar>(pixelr * alpha + beta);
                            }
                            if (valor == 7)
                            {
                                
                                anterior.at<Vec3b>(r, c)[0] = pixelb;//saturate_cast<uchar>(pixelb * alpha + beta);
                                anterior.at<Vec3b>(r, c)[1] = pixelg; //saturate_cast<uchar>(pixelg * alpha + beta);
                                anterior.at<Vec3b>(r, c)[2] = saturate_cast<uchar>(pixelr * alpha + beta);
                            }

                            c = c + 1;
                        }
                        gurda = c;
                        c = gurda2;

                        r = r + 1;
                    }

                    c = gurda;
                    gurda2 = c;

                    gurda3 = r;
                    r = gurda4;
                }
                

                r = gurda3;
                gurda4 = r;
            }
            
            // imagencont = imagencont + 1;
            //resize(anterior,anterior,Size(),1.5,1.5);
            createTrackbar("Color", "Video", &valor, 7, eventoTrack, NULL);
            
            videoEfecto.write(anterior);
            imshow("Video", frame);

            imshow("Movimiento2", anterior);

            if (waitKey(33) == 27)
            {
                break;
            }
        }

        video.release();
        videoGrabado.release();
        videoEfecto.release();
        
        destroyAllWindows();
    }
}
