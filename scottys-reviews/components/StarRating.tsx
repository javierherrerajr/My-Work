// components/StarRating.tsx
"use client";

import { Star, StarHalf } from "lucide-react";
import React from "react";

interface StarRatingProps {
  rating: number; // Accepts values from 0 to 10 (e.g., 8.5)
  size?: number; // Optional size in px (default 20)
  className?: string;
  onClick?: (rating: number) => void; // Add onClick handler
}

export const StarRating: React.FC<StarRatingProps> = ({
  rating,
  size = 20,
  className = "",
  onClick,
}) => {
  // Ensure rating is between 0 and 10
  const validRating = Math.max(0, Math.min(10, Number(rating) || 0));
  const fullStars = Math.floor(validRating);
  const hasHalfStar = validRating - fullStars >= 0.5;
  const emptyStars = 10 - fullStars - (hasHalfStar ? 1 : 0);

  return (
    <div
      className={`flex items-center gap-1 ${className}`}
      data-testid="star-rating-container"
    >
      {[...Array(fullStars)].map((_, i) => (
        <Star
          key={`full-${i}`}
          fill="currentColor"
          stroke="none"
          width={size}
          height={size}
          onClick={() => onClick && onClick(i + 1)}
          data-testid="star-full"
          role="img"
        />
      ))}
      {hasHalfStar && (
        <StarHalf
          fill="currentColor"
          stroke="none"
          width={size}
          height={size}
          onClick={() => onClick && onClick(fullStars + 0.5)}
          data-testid="star-half"
          role="img"
        />
      )}
      {[...Array(emptyStars)].map((_, i) => (
        <Star
          key={`empty-${i}`}
          className="opacity-30"
          width={size}
          height={size}
          onClick={() =>
            onClick && onClick(fullStars + (hasHalfStar ? 1 : 0) + i + 1)
          }
          data-testid="star-empty"
          role="img"
        />
      ))}
    </div>
  );
};
