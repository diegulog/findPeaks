package com.diegulog.findpeaksinf

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.widget.TextView
import androidx.lifecycle.lifecycleScope
import com.diegulog.findpeaksinf.databinding.ActivityMainBinding
import kotlinx.coroutines.Dispatchers
import kotlinx.coroutines.launch
import kotlinx.coroutines.withContext
import java.util.concurrent.Executors
import java.util.concurrent.TimeUnit

class MainActivity : AppCompatActivity() {
    private val executor = Executors.newSingleThreadScheduledExecutor()


    private lateinit var binding: ActivityMainBinding

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        binding = ActivityMainBinding.inflate(layoutInflater)
        setContentView(binding.root)


        val result = findPeaksFromJNI(mag, 5)

        binding.sampleText.text = arrayOf(result).contentDeepToString()


        executor.scheduleWithFixedDelay({
            findPeaksFromJNI(mag, 5)
            },
            0,
            200,
            TimeUnit.MILLISECONDS
        )

    }


    /**
     * A native method that is implemented by the 'findpeaksinf' native library,
     * which is packaged with this application.
     */
    external fun findPeaksFromJNI(mag: DoubleArray, minPeakDistance: Int): DoubleArray



    companion object {
        // Used to load the 'findpeaksinf' library on application startup.
        init {
            System.loadLibrary("findpeaksinf")
        }
    }
    val mag = doubleArrayOf(
        0.012359637,
        0.010296234,
        0.010509006,
        0.009696282,
        0.011536455,
        0.012155394,
        0.012031682,
        0.012481398,
        0.010455102,
        0.011052487,
        0.011997733,
        0.01008767,
        0.008855798,
        0.008688111,
        0.010806825,
        0.01123014,
        0.010851607,
        0.009548519,
        0.009192471,
        0.009826579,
        0.014116371,
        0.016267091,
        0.01990906,
        0.027646821,
        0.030021384,
        0.03345409,
        0.056132734,
        0.1094252,
        0.111169755,
        0.123612866,
        0.15026765,
        0.1440818,
        0.12972009,
        0.120515205,
        0.10780328,
        0.09580766,
        0.115186684,
        0.14270815,
        0.2039818,
        0.18946342,
        0.21765703,
        0.2525728,
        0.25276202,
        0.22271425,
        0.2061444,
        0.18387191,
        0.16692606,
        0.14763953,
        0.13296196,
        0.11005399,
        0.10604996,
        0.14938019,
        0.20566179,
        0.19123286,
        0.23135923,
        0.2458125,
        0.2681597,
        0.25021514,
        0.21739636,
        0.18777825,
        0.17868224,
        0.15581156,
        0.12930901,
        0.12438294,
        0.17762277,
        0.24063078,
        0.27217564,
        0.2706589,
        0.30598658,
        0.3740903,
        0.31355163,
        0.27388555,
        0.24331053,
        0.21392842,
        0.18642063,
        0.16289707,
        0.17064013,
        0.22105405,
        0.20354393,
        0.16743423,
        0.22035891,
        0.27909222,
        0.32131433,
        0.2750773,
        0.23504344,
        0.1991862,
        0.17580393,
        0.16645516,
        0.15114357,
        0.13253523,
        0.24107853,
        0.20476775,
        0.25534433,
        0.3263236,
        0.31763828,
        0.26121914,
        0.25586694,
        0.24500993,
        0.22244938,
        0.19894597
    )

}