(
Server.local.boot;
~port = SerialPort.new("/dev/tty.usbmodem101", 9600);
~charArray = [ ];

~getValues = Routine.new({
	var ascii;
	{
		ascii = ~port.read.asAscii;
		if(ascii.isDecDigit, {
				~charArray = ~charArray.add(ascii);
		});

		if(ascii == $b) {
			~valA = ~charArray.collect(_.digit).convertDigits;
			~charArray = [ ];
		};

		if(ascii == $a) {
			~valB = ~charArray.collect(_.digit).convertDigits;
			~charArray = [ ];
		};

		if(ascii == $d) {
			~valC = ~charArray.collect(_.digit).convertDigits;
			~charArray = [ ];
		};

		if(ascii == $c) {
			~valD = ~charArray.collect(_.digit).convertDigits;
			~charArray = [ ];
		};

	}.loop;
}).play;
)

// Uncomment to test
//~valA; // y-value for joystick 1
//~valB; // y-value for joystick 2
//~valC; // x-value for joystick 1
//~valD; // x-value for joystick 2

// This synthdef was modified from https://composerprogrammer.com/teaching/supercollider/sctutorial/12.2%20Singing%20Voice%20Synthesis.html
(
SynthDef(\voicesound,{|voiced=0.9 freq= 300 amp=0.1 resonancescaling=7 cutoff=1000 delay=0.25 shaky=1|
var formantfreqs, formantamps, formantbandwidths; //data for formants
var periodicsource, aperiodicsource, source, output;
var vibrato;
var vibratonoise= LFNoise1.kr(shaky);
formantfreqs= [800,1150,2900,3900,4950]; //centre frequencies of formants
formantamps= ([0 ,-6,-32,-20,-50]-6).dbamp; //peaks of formants
formantbandwidths=[80,90,120,130,140];  //bandwidths
//with vibrato up to quartertone, rate of vibrato around 6+-1 Hz
//calculate vibrato in midi note (log frequency) domain; final .midicps takes it back to frequency
//line generator delays onset of vibrato like a real singer
vibrato= ((freq.cpsmidi)+(Line.kr(0.0,1.0,2.5)*SinOsc.kr(6+(1.0*vibratonoise),0,0.5))).midicps;
// low pass filter on Impulse to avoid high harmonics making it too bright
periodicsource= LPF.ar(Impulse.ar(vibrato),5000);
//pink noise drops off as frequency increases at -dB per octave,
aperiodicsource= PinkNoise.ar(0.7);
//take now as mixture of periodic and aperiodic
source= (voiced*periodicsource)+((1.0-voiced)*aperiodicsource);
//the decaytime of the formlet is the filter's resonant decay time; a small bandwidth corresponds to a long decay (a 'ringing' filter). So I take the reciprocal of the formant bandwidth as an estimate of decaytime here, multiplied by a scaling factor for degree of resonance
output= Mix(Formlet.ar(source, formantfreqs, 0.001, resonancescaling*formantbandwidths.reciprocal, formantamps))*10*amp;
output = RLPF.ar(output.dup, cutoff.lag(0.02), 0.25, 0.2);

Out.ar(0,output);

}).add
)

FreqScope.new(1000,700);

a= Synth(\voicesound);

(
~control = Routine.new({
	{
		a.set(\freq, ~valA.linexp(0, 1023, 100, 600)); // pitch
		a.set(\cutoff, (~valC.linexp(0, 1023, 300, 3000) + (~valD.linexp(0, 1023, 3000, 300)))); // bawao

		a.set(\voiced, ~valB.linexp(0, 1023, 0.8, 1)); // wheeze
		a.set(\amp, ~valB.linexp(0, 1023, 0.01, 0.25)); // volume

		0.01.wait;
	}.loop;
}).play;
)