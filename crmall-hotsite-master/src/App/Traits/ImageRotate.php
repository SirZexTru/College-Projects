<?php
namespace App\Traits;

trait ImageRotate
{
    public function rotate($file, $degrees)
    {
        $source = @imagecreatefromjpeg($file);
        $rotate = imagerotate($source, $degrees, 0);

        return imagejpeg($rotate, $file);
    }
}
