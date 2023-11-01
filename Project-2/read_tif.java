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

    private static BufferedImage orderedDither(BufferedImage image, int[][] mat) {
        BufferedImage result_image  = new BufferedImage(width, height,BufferedImage.TYPE_BYTE_GRAY);

        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                int original_value = image.getRGB(x, y) & 0xFF;
                int dither_Value = mat[x % mat.length][y % mat[0].length];
                
                if (original_value%(mat.length*mat.length+1) > dither_Value) {
                    result_image.setRGB(x, y, 0);
                } else {
                    result_image.setRGB(x, y, 0xFFFFFF);
                }
            }
        }
        return result_image;
    }

    private static BufferedImage orderedDither_output(BufferedImage image) {
        int[][] mat = {
            {0, 32, 8, 40, 2, 34, 10, 42},
            {48, 16, 56, 24, 50, 18, 58, 26},
            {12, 44, 4, 36, 14, 46, 6, 38},
            {60, 28, 52, 20, 62, 30, 54, 22},
            {3, 35, 11, 43, 1, 33, 9, 41},
            {51, 19, 59, 27, 49, 17, 57, 25},
            {15, 47, 7, 39, 13, 45, 5, 37},
            {63, 31, 55, 23, 61, 29, 53, 21}
        };
        
        return orderedDither(image,mat);
    }

    private static double[] calculateCDF(BufferedImage image,char channel) {
        int[] count = new int[256];
        for(int i =0; i<256;i++){
            count[i] = 0;
        }
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                int rgb = image.getRGB(x, y);
                int colorValue = 0;

                if (channel == 'r') {
                    colorValue = (rgb >> 16) & 0xFF; // Red channel
                } else if (channel == 'g') {
                    colorValue = (rgb >> 8) & 0xFF; // Green channel
                } else if (channel == 'b') {
                    colorValue = rgb & 0xFF; // Blue channel
                }
                count[colorValue]++;
            }
        }
        int sum = 0;
        for(int i =0; i<256;i++){
            sum+=count[i];
        }
        double[] cdf = new double[256];
        int step = 0;
        for(int i =0; i<256;i++){
            step+=count[i];
            cdf[i] = (double) step/sum;
            //System.out.println(cdf[i]);
        }
        return cdf;
    }

    private static BufferedImage atuoLevel_output(BufferedImage image) {
        BufferedImage result_image = new BufferedImage(width, height,BufferedImage.TYPE_INT_RGB);
        double[] cdf_r = calculateCDF(image,'r');
        double[] cdf_b = calculateCDF(image,'b');
        double[] cdf_g = calculateCDF(image,'g');

        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                int rgb = image.getRGB(x, y);

                int r = (rgb >> 16) & 0xFF;
                int g = (rgb >> 8) & 0xFF;
                int b = rgb & 0xFF;
                r = (int)(cdf_r[r] * 255.0);
                g = (int)(cdf_g[g] * 255.0);
                b = (int)(cdf_b[b] * 255.0);
                int result = (r << 16) | (g << 8) | b;
                result_image.setRGB(x, y, result);
            }
        }
        return result_image;
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
            case 2:
                left = Grayscale();
                right = orderedDither_output(Grayscale());
                break;
            case 3:
                left = image;
                right = atuoLevel_output(image);
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

