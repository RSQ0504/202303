import java.io.File;
import java.io.IOException;

import javax.imageio.ImageIO;
import javax.swing.JPanel;

import java.awt.*;
import java.awt.image.BufferedImage;

public class read_tif extends JPanel{
    private static BufferedImage image;
    private int page = 0;
    private static int width;
    private static int height;

    public read_tif(String imagePath) {
        try {
            image = ImageIO.read(new File(imagePath));
            width = image.getWidth();
            height = image.getHeight();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public BufferedImage Grayscale() {
        BufferedImage grey_image  = new BufferedImage(width, height,BufferedImage.TYPE_BYTE_GRAY);

        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                int c_value = image.getRGB(x, y);
                int r = (c_value >> 16) & 0xFF; 
                int g = (c_value >> 8) & 0xFF;  
                int b = c_value & 0xFF;

                int gray = (r + g + b) / 3;

                int grayPixel = (gray << 16) | (gray << 8) | gray;
                grey_image.setRGB(x, y, grayPixel);
            }
        }
        return grey_image;
    }

    public BufferedImage ReduceBright(BufferedImage i){
        BufferedImage copy;
        if (i.getType() == 0){
            copy  = new BufferedImage(width, height,BufferedImage.TYPE_INT_RGB);
        }else{
            copy  = new BufferedImage(width, height,i.getType());
        }
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                int rgb = i.getRGB(x, y);

                int r = (rgb >> 16) & 0xFF;
                int g = (rgb >> 8) & 0xFF;
                int b = rgb & 0xFF;
                r = (int)(r * 0.5);
                g = (int)(g * 0.5);
                b = (int)(b * 0.5);
                int result = (r << 16) | (g << 8) | b;
                copy.setRGB(x, y, result);
            }
        }
        return copy;
    }


    public void draw(){
        setLayout(new BorderLayout());
        repaint(); 
    }

    @Override
    protected void paintComponent(Graphics g) {
        super.paintComponent(g);
        double scale_a = (double) width/350;
        double scale_b = (double) height/250;
        double s = (scale_a>scale_b)?scale_a:scale_b;
        //System.out.println(s);
        int scale = (int) Math.ceil(s);
        //System.out.println(scale);
        int scale_w=width/scale;
        int scale_h=height/scale;
        BufferedImage left;
        BufferedImage right;

        switch (page) {
            case 0:
                left = image;
                right = Grayscale();
                break;
            case 1:
                left = ReduceBright(image);
                right = ReduceBright(Grayscale());
                break;
            default:
                left = image;
                right = Grayscale();
                page = 0;
                break;
        }
        page+=1;
        g.drawImage(left, 0, 0, scale_w, scale_h, null);
        g.drawImage(right, scale_w + 10, 0, scale_w, scale_h, null);
    }
}

