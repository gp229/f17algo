private function triple_exponential_smoothing($series, $slen, $alpha, $beta, $gamma, $num_predictions)
        {
                $tempTime = end($series);
                $tempTime = $tempTime['timestamp'];
                $series = array_column($series, "close");
                $num_seasons = count($series)/$slen;
                for($j=0;$j < $num_seasons;$j++)
                {
                        $season_averages[$j] = array_sum(array_slice($series, $slen*$j,$slen*$j+$slen))/$slen;
                }
                for($i=0;$i < $slen;$i++)
                {
                        $sum_of_vals_over_avg = 0.0;
                        for($j=0;$j < $num_seasons;$j++)
                        {
                                $sum_of_vals_over_avg += $series[$slen*$j+$i]-$season_averages[$j];
                        }
                        $seasonals[$i] = $sum_of_vals_over_avg/$num_seasons;
                }
                for($i=0;$i < $slen;$i++)
                {
                        $sum = 0;
                        $sum += ($series[$i+$slen] - $series[$i]) / $slen;
                }
                $trend = $sum / $slen;
                $smooth = $series[0];
                $result = array();
                for($i=1;$i < count($series) + $num_predictions;$i++)
	            {
                        if($i >= count($series))
                        {
                                $m = $i - count($series) + 1;
                                $tempTime = date('Y-m-d H:i:00', strtotime($tempTime.'+1 minute'));
                                if(date('N',strtoTime($tempTime)) == '6')
                                {
                                        $tempTime = date('Y-m-d 09:30:00', strtotime($tempTime.'+2 day'));
                                }
                                elseif(date('N',strtoTime($tempTime)) == '7')
                                {
                                        $tempTime = date('Y-m-d 09:30:00', strtotime($tempTime.'+1 day'));
                                }
                                if(date('Hi',strtoTime($tempTime)) > '1600')
                                {
                                        $tempTime = date('Y-m-d 09:30:00', strtotime($tempTime.'+1 day'));
                                }
                                $tempArray['timestamp'] = $tempTime;
                                $tempArray['close'] = ($smooth + $m*$trend) + $seasonals[$i%$slen];
                                array_push($result, $tempArray);
                        }
                        else
                        {
                                $val = $series[$i];
                                $last_smooth = $smooth;
                                $smooth = $alpha*($val-$seasonals[$i%$slen]) + (1-$alpha)*($smooth+$trend);
                                $trend = $beta * ($smooth-$last_smooth) + (1-$beta)*$trend;
                                $seasonals[$i%$slen] = $gamma*($val-$smooth) + (1-$gamma)*$seasonals[$i%$slen];
                        }
                }
                return $result;
        }
