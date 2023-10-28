import java.io.File;
import java.io.IOException;

import javax.imageio.ImageIO;
import javax.swing.JPanel;

import java.awt.*;
import java.awt.image.BufferedImage;

public class read_tif extends JPanel{
    private BufferedImage image;

    public read_tif(String imagePath) {
        try {
            image = ImageIO.read(new File(imagePath));
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
    public BufferedImage Grayscale() {
        int width = image.getWidth();
        int height = image.getHeight();
        BufferedImage grey_image  = new BufferedImage(width, height,BufferedImage.TYPE_BYTE_GRAY);

        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                int c_value = image.getRGB(x, y);
                int r = (c_value >> 16) & 0xFF; 
                int g = (c_value >> 8) & 0xFF;  
                int b = c_value & 0xFF;

                int gray = (r + g + b) / 3; // Calculate the grayscale value

                int grayPixel = (gray << 16) | (gray << 8) | gray;
                grey_image.setRGB(x, y, grayPixel);
            }
        }
        return grey_image;
    }
    public void draw(){
        setLayout(new BorderLayout());
        repaint(); 
    }

    @Override
    protected void paintComponent(Graphics g) {
        super.paintComponent(g);
        BufferedImage grey = Grayscale();
        if (image.getWidth()>350||image.getHeight()>250){
            double scale_a = (double) image.getWidth()/350;
            double scale_b = (double) image.getHeight()/250;
            double s = (scale_a>scale_b)?scale_a:scale_b;
            //System.out.println(s);
            int scale = (int) Math.ceil(s);
            //System.out.println(scale);
            int scale_w=image.getWidth()/scale;
            int scale_h=image.getHeight()/scale;
            g.drawImage(image, 0, 0, scale_w, scale_h, null);
            g.drawImage(grey, scale_w + 10, 0, scale_w, scale_h, null);
        }else{
            g.drawImage(image, 0, 0, null);
            g.drawImage(grey, image.getWidth()+10, 0, null);
        }
    }
}

