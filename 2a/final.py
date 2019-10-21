import simpleaudio as sa
import time
import random
import math
import midiutil

print("Initializing PolyGen")
program = ("on")

# create state variable and set program to start at initial state
state = ("input")

# create while loop to be able to switch between diffrent program states
while program == ("on"):
    while state == ("input"):
        # user sets bpm
        bpm = (input("Set bpm "))
        # user sets 2 timesignatures
        timeSig1 = (input("Set time signature one "))
        timeSig2 = (input("Set time signature two "))
        bars = input("How many bars would you like to generate? ")

        try:
            # checks if the input values aren't 0
            # checks if the input values can be converted to floats
            1 % float(bpm)
            1 % float(timeSig1[0])
            1 % float(timeSig1[2])
            1 % float(timeSig2[0])
            1 % float(timeSig2[2])
            1 % float(bars)

            # Checks if the timesignature is set correctly
            math.sqrt(timeSig1.find('/'))
            math.sqrt(timeSig2.find('/'))

            # checks if the input values are positive
            math.sqrt(float(bpm))
            math.sqrt(float(timeSig1[0]))
            math.sqrt(float(timeSig1[2]))
            math.sqrt(float(timeSig2[0]))
            math.sqrt(float(timeSig2[2]))
            math.sqrt(float(bars))
        except:
            print("Something went wrong")
            print("Use only positive numbers")
            print("Set time signatures as two numbers seperated by a forward slash")
        else:
            state = ("algorithm")

    while state == ("algorithm"):
        quarterNoteDuration = 60 / float(bpm)
        # calculate the duration of a sixteenth note
        sixteenthNoteDuration = quarterNoteDuration / 4.0

        # timeSig1Steps = float(timeSig1) * (timeSig1[0] / timeSig2[2])

        # calculates how many 16th notes are in each time signature
        # calculates how long the sequence must be
        timeSig1Steps = ((float(timeSig1[0]) / float(timeSig1[2])) * 16)
        timeSig1Steps = timeSig1Steps * float(bars)
        timeSig2Steps = ((float(timeSig2[0]) / float(timeSig2[2])) * 16)
        timeSig2Steps = timeSig2Steps * float(bars)
        # create list where 'note timestamps' will be placed as 16th notes,
        # indicating at which time the sample must be played
        timestamps16thI1 = []
        timestamps16thI2 = []
        timestamps16thI3 = []

        # sets starting position for algorithm
        currentStep = 0

        # creates note timestamps for instrument 1 sample algorithmicaly
        while currentStep < timeSig1Steps:
            # if currentstep is at the start of a bar,
            # fills step and advances two or three steps
            if currentStep % float(timeSig1Steps) == 0:
                timestamps16thI1.append(currentStep)
                currentStep = currentStep + random.randint(2, 3)
            # chance to fill step and advance two or three steps
            elif random.randint(0, 100) > random.randint(25, 50):
                timestamps16thI1.append(currentStep)
                currentStep = currentStep + random.randint(2, 3)
            # if step not filled, advance two or three steps
            else:
                currentStep = currentStep + random.randint(2, 3)

        # resets starting position for algorithm
        currentStep = 0

        while currentStep < timeSig1Steps:
            if currentStep % float(timeSig2Steps) == 0:
                timestamps16thI2.append(currentStep)
                currentStep = currentStep + random.randint(2, 3)
            elif random.randint(0, 100) > random.randint(25, 50):
                timestamps16thI2.append(currentStep)
                currentStep = currentStep + random.randint(2, 3)
            else:
                currentStep = currentStep + random.randint(2, 3)

        currentStep = 0

        while currentStep < timeSig1Steps:
            if currentStep % float(timeSig2Steps) == 0:
                timestamps16thI3.append(currentStep)
                currentStep = currentStep + random.randint(2, 3)
            elif random.randint(0, 100) > random.randint(25, 50):
                timestamps16thI3.append(currentStep)
                currentStep = currentStep + random.randint(2, 3)
            else:
                currentStep = currentStep + random.randint(2, 3)

        # creates a list to hold dictionarys
        dictList = []

        # transform the sixteenthTimestamps to time values
        # creates dictionary for time value and add to list
        # adds instrument value and quarternoteStamp
        for timestamp in timestamps16thI1:
          playTime = (timestamp * sixteenthNoteDuration)
          stamp = {'timestamp': playTime, 'instrument': 0,
          'quarternoteStamp': timestamp}
          dictList.append(stamp)

        for timestamp in timestamps16thI2:
          playTime = (timestamp * sixteenthNoteDuration)
          stamp = {'timestamp': playTime, 'instrument': 1,
          'quarternoteStamp': timestamp}
          dictList.append(stamp)

        for timestamp in timestamps16thI3:
          playTime = (timestamp * sixteenthNoteDuration)
          quarternoteStamp = timestamp
          stamp = {'timestamp': playTime, 'instrument': 2,
          'quarternoteStamp': timestamp}
          dictList.append(stamp)

        # sorts the list with dictionarys according to timestamp
        dictList = sorted(dictList, key = lambda i: i['timestamp'])

        # copys timestamps into a new list to be used later
        dictListBank = dictList.copy()

        # loads 3 audioFiles and store it into a list
        I0 = sa.WaveObject.from_wave_file("Kick.wav")
        I1 = sa.WaveObject.from_wave_file("Bell.wav")
        I2 = sa.WaveObject.from_wave_file("Conga.wav")
        samples = [I0, I1, I2]

        state = ("playSeq")


    while state == ("playSeq"):
        print("Playing sequence...")
        # how many times the sequence will be played
        loopAmount = 1

        for i in range(loopAmount):
            # pops the first dictionary off the list
            # pops payload out of the dictionary
            dictionary = dictList.pop(0)
            timestamp = dictionary['timestamp']
            sample = dictionary['instrument']

            # sets time/resets clock
            startTime = time.time()

            # play the sequence
            while True:
              # retrieve current time
              currentTime = time.time()

              # check whether the current time is beyond the timestamp's time,
              # meaning it is time to play the sample
              if(currentTime - startTime >= timestamp):
                samples[sample].play()

                # if there are timestamps left in the timestamps list
                if dictList:
                  # retrieve the next payload
                  dictionary = dictList.pop(0)
                  timestamp = dictionary['timestamp']
                  sample = dictionary['instrument']
                else:
                  # if there are no timestamps left in list,
                  # replenishes the timestamps list and breaks loop
                  dictList = list.copy(dictListBank)
                  time.sleep(quarterNoteDuration)
                  break

              else:
                # short wait to prevent we'll keep the processor busy when there's
                # nothing to do
                time.sleep(0.001)

            state = ("options")

    # if the sequence is finished
    while state == ("options"):
        # prints options
        print("To export sequence to MIDI file, enter 'export'")
        print("To enter new parameters, enter 'reset'")
        print("To generate another rhythm with same parameters, enter 'reroll'")
        choice = str((input("To exit the program, enter 'exit' ")))

        # sets state according to input
        if choice == ("reset"):
            print("Resetting...")
            state = ("input")
        elif choice == ("reroll"):
            print("Rerolling...")
            state = ("algorithm")
        elif choice == ("exit"):
            print("Exiting program...")
            state = ("exit")
        elif choice == ("export"):
            state = ("writeMIDI")
        else:
            print("Something went wrong")


    while state == ("writeMIDI"):
        dictList = list.copy(dictListBank)
        from midiutil import MIDIFile

        name = input("What do you want to name your MIDI file? ")

        track    = 0 # set midi track
        channel  = 10 # set midi channel
        tempo    = 60   # In BPM
        volume   = 100  # 0-127, as per the MIDI standard

        # creates midi file and adds data
        MyMIDI = MIDIFile(1)
        MyMIDI.addTempo(track, 0, tempo)

        # pops information out of dictionarys and adds to midi file
        while True:
            if dictList:
                dictionary = dictList.pop(0)
                midiStamp = int(dictionary['quarternoteStamp'])
                midiNote = int(dictionary['instrument']) + 60
                MyMIDI.addNote(track, channel, midiNote, midiStamp, 0.25, volume)
            else:
                with open(name + ".mid", "wb") as output_file:
                    MyMIDI.writeFile(output_file)
                print("Midi file exported")
                break

        state = ("options")


    if state == ("exit"):
        break
