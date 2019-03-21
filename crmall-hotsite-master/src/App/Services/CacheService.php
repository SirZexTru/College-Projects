<?php

namespace App\Services;

class CacheService
{
    public $fileSystemDir = PATH_CACHE;

    public $tempPath = PATH_CACHE . '/temp';

    /**
     * @var int Expiration cache
     *         Default is 15 minutes
     */
    private $expiration = 900;

    public function __construct(array $options = [])
    {
        if (isset($options['expiration'])) {
            $this->expiration = $options['expiration'];
        }

        if (isset($options['tempPath'])) {
            $this->tempPath = $options['tempPath'];
        }

        if (isset($options['cacheDir'])) {
            $this->fileSystemDir = $options['cacheDir'];
        }
    }

    public function setCacheDir($dir)
    {
        $this->fileSystemDir = $dir;
    }

    public function setExpiration($expiration)
    {
        $this->expiration = $expiration;
    }

    public function get($key, $expired = false)
    {
        $fileName = $this->getFileName($key);

        if (is_file($fileName)) {
            $time = filemtime($fileName);
            $content = file_get_contents($fileName);
            $data = unserialize($content);

            if ((int)$data['expiration'] === 0 || $data['expiration'] >= time() - $time) {
                return $expired?['expired' => false, 'data' => $data['data']]:$data['data'];
            } elseif ($expired) {
                return $data['data'];
            }

            $this->delete($key);
        }

        return false;
    }

    public function save($key, $data, $expiration = null)
    {
        if ($expiration == null) {
            $expiration = $this->expiration;
        }

        $data = [
            'expiration' => $expiration,
            'data' => $data
        ];

        $file = $this->getFileName($key);

        return file_put_contents($file, serialize($data));
    }

    public function delete($key)
    {
        $fileName = $this->getFileName($key);

        if (is_file($fileName)) {
            return unlink($fileName);
        }

        return false;
    }

    private function getFileName($key)
    {
        $dir = $this->fileSystemDir;

        if (!is_dir($dir)) {
            mkdir($dir, 0775, true);
        }

        return $dir . '/' . md5($key) . '.data';
    }
}
